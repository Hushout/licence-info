boost::future<void> DropboxService::putFile(std::istream& source, std::string target)
{
    std::shared_ptr<std::stringstream> out(new std::stringstream);
    json payload = {
        {"path", target},
        {"mode", "overwrite"},
        {"mute", true},
    };

    return _sender.send(
        HTTP::Request()
            .setVerb(HTTP::Verb::POST)
            .setUrl(CONTENT_BASE_URL + "files/upload")
            .addHeader("Authorization", "Bearer " + _token)
            .addHeader("Dropbox-API-Arg", payload.dump())
            .setFile(&source),
        out.get()
    ).then([out, &source, target, this](boost::future<HTTP::Response> future)
    {
        HTTP::Response res = future.get();

        if (res.getCode() != 200)
        {
            throw std::runtime_error("Impossible d'envoyer le fichier.");
        }
    });
}

boost::future<void> DropboxService::fetchFile(std::string source, std::ostream& target)
{
    json payload = {{"path", source}};

    return _sender.send(
        HTTP::Request()
            .setVerb(HTTP::Verb::POST)
            .setUrl(CONTENT_BASE_URL + "files/download")
            .addHeader("Authorization", "Bearer " + _token)
            .addHeader("Dropbox-API-Arg", payload.dump()),
        &target
    ).then([](boost::future<HTTP::Response> future)
    {
        HTTP::Response res = future.get();

        if (res.getCode() != 200)
        {
            throw std::runtime_error("Impossible de recevoir le fichier.");
        }
    });
}

boost::future<Quota> DropboxService::getQuota()
{
    std::shared_ptr<std::stringstream> out(new std::stringstream);

    return _sender.send(
        HTTP::Request()
            .setVerb(HTTP::Verb::POST)
            .setUrl(API_BASE_URL + "users/get_space_usage")
            .addHeader("Authorization", "Bearer " + _token),
        out.get()
    ).then([out](boost::future<HTTP::Response> future)
    {
        HTTP::Response res = future.get();

        if (res.getCode() != 200)
        {
            throw std::runtime_error(
                "Impossible de récupérer le quota."
            );
        }

        json data;
        data << *out;

        return Quota(data["used"], data["allocation"]["allocated"]);
    });
}
