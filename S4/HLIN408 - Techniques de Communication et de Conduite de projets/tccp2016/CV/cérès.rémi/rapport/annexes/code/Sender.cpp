// (...)
Sender::Sender()
: _send_running(false), _multi(curl_multi_init())
{}

Sender::~Sender()
{
    // Si le thread d’envoi a été démarré, on veut désormais le stopper
    if (_send_worker.joinable())
    {
        {
            // Réveil du thread et demande d’arrêt
            std::lock_guard<std::mutex> wakeup_lock(_wakeup_mutex);
            _send_running = false;
            _send_wakeup.notify_one();
        }

        // Jonction des deux fils d’exécution
        _send_worker.join();
    }

    // Libération de la file d’attente cURL
    curl_multi_cleanup(_multi);
}

boost::future<Response> Sender::send(Request& req, std::ostream* out)
{
    _start();

    // Mise en attente d'une instance cURL pour la nouvelle requête
    std::lock_guard<std::mutex> sendings_lock(_sendings_mutex);
    CURL* simple = _prepare(req, out);

    // Réveil du thread d’envoi pour la prise en charge de la requête
    std::lock_guard<std::mutex> wakeup_lock(_wakeup_mutex);
    _send_wakeup.notify_one();

    return _sendings_infos[simple].promise.get_future();
}

// (...)
void Sender::_start()
{
    if (!_send_running)
    {
        _send_running = true;

        // Si le thread d'envoi a rencontré une erreur, on l'arrête
        if (_send_worker.joinable())
        {
            _send_worker.join();
        }

        // Lancement du thread d'envoi
        _send_worker = std::thread(&Sender::_sendWorker, this);
    }
}

CURL* Sender::_prepare(Request& base_req, std::ostream* out)
{
    // Récupération d'une instance de cURL depuis la piscine
    CURL* simple = _pool.pop();

    // Création d'un objet d'informations sur l'envoi. Les informations sur
    // la requête sont copiées afin de rester accessibles tout au long de
    // l'envoi.
    _sendings_infos[simple] = {
        base_req,
        Response(),
        boost::promise<Response>()
    };

    // (...)
    // Ajout de la nouvelle instance dans la file d'attente
    _pending_sendings.push(simple);

    return simple;
}

void Sender::_fulfill(CURL* simple)
{
    // Recherche des informations sur l'envoi à associé à l'instance donnée
    auto infos_search = _sendings_infos.find(simple);

    // Recherche de l'instance dans la liste des envois en cours
    auto current_search = std::find(
        _current_sendings.begin(),
        _current_sendings.end(),
        simple
    );

    if (
        infos_search != _sendings_infos.end() &&
        current_search != _current_sendings.end()
    )
    {
        _SendingInfo& info = infos_search->second;

        // Remplissage du code de réponse HTTP
        long response_code = 0;
        curl_easy_getinfo(
            simple,
            CURLINFO_RESPONSE_CODE,
            &response_code
        );

        info.res.setCode(response_code);

        // Satisfaction de la promesse associée à la requête
        info.promise.set_value(std::move(info.res));

        // Suppression des informations pour cet envoi
        _sendings_infos.erase(infos_search);

        // Suppression de la liste des envois en cours
        _current_sendings.erase(current_search);

        curl_multi_remove_handle(_multi, simple);
    }

    // Dans tous les cas, libération de la ressource
    _pool.push(simple);
}

void Sender::_sendWorker()
{
    CURLMcode code;
    int unused = 0;
    int file_descriptors = 0;

    while (_send_running)
    {
        // Demande de réalisation des envois associés aux requêtes cURL
        // en attente (non-bloquant)
        code = curl_multi_perform(_multi, &unused);

        if (code != CURLM_OK)
        {
            _send_running = false;
            break;
        }

        // Attente de la réalisation des envois ou au plus une seconde
        code = curl_multi_wait(_multi, NULL, 0, 1000, &file_descriptors);

        if (code != CURLM_OK)
        {
            _send_running = false;
            break;
        }

        if (file_descriptors == 0)
        {
            // cURL nous signale qu’on ne peut pas savoir quand se terminera
            // le travail en cours. On attend donc 200 ms.
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        std::unique_lock<std::mutex> sendings_lock(_sendings_mutex);

        // Si certains envois sont terminés, satisfaction des promesses
        CURLMsg* message = curl_multi_info_read(_multi, &unused);

        while (message != nullptr)
        {
            if (message->msg == CURLMSG_DONE)
            {
                _fulfill(message->easy_handle);
            }

            message = curl_multi_info_read(_multi, &unused);
        }

        // S'il y a moins d'envois en cours que le nombre maximal autorisé
        // d'envois parallèles, et s'il y a des envois en attente, on peut
        // retirer des éléments de la file d'attente et les lancer
        while (
            !_pending_sendings.empty() &&
            _current_sendings.size() < _concurrency
        )
        {
            CURL* simple = _pending_sendings.front();
            Request& req = _sendings_infos[simple].req;

            _pending_sendings.pop();

            _current_sendings.push_back(simple);
            curl_multi_add_handle(_multi, simple);
        }

        // Si plus aucun envoi n'est en attente, on met en sommeil
        // le thread
        if (_current_sendings.size() == 0 && _send_running)
        {
            std::unique_lock<std::mutex> wakeup_lock(_wakeup_mutex);
            sendings_lock.unlock();
            _send_wakeup.wait(wakeup_lock);
        }
    }
}
