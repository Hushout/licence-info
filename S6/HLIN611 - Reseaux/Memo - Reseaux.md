# MODELE OSI

Open Systems Interconnection est un standard de communication, en réseau, de tous les systèmes informatiques. 

| N° | Couche       | Fonction                                                      | Exemple                       |
|----|--------------|---------------------------------------------------------------|-------------------------------|
| 7  | Application  | Point d'accès aux services réseaux                            | HTTP, FTP, NFS, DNS, SSH      |
| 6  | Présentation | Convertit les données machine en données exploitables         | ASCII, Unicode, MIME          |
| 5  | Session      | Gère les communication entre les différentes applications     | NetBIOS, RPC, ASP, SOCKS      |
| 4  | Transport    | Connexion de bout en bout et contrôle de flux, notion de port | TCP, UDP, SCTP, SPX, ATP      |
| 3  | Réseau       | Détermine le parcours des données et l'adressage logique      | IPv4, IPv6, ICMP, IGMP        |
| 2  | Liaison      | Adressage physique (adresse MAC)                              | Ethernet, Wi-Fi ,Token Ring   |
| 1  | Physique     | Transmission des signaux sous forme numérique ou analogique   | ADSL, Radio, Laser, Bluetooth |

# RESEAUX TCP/IP

Une adresse IP est constituée de deux parties : 
L'adresse du réseau et l'adresse de la machine, elle permet de distinguer une machine sur un réseau (net-id).
Deux machines se trouvant sur un même réseau possèdent la même adresse réseau mais pas la même adresse machine (host-id).

## ADRESSAGE IPv4

Les adresses IPv4 sont representées par 4 entiers variants de 0 à 255 (sur 4 * 8 bits = 32 bits)

172.16.254.1 (Notation decimale à point) => 10101100 00010000 11111110 00000001 (En binaire)

## ADRESSAGE IPv6

Les adresses IPv6 sont codées sur 128 bits et representées par 8 paquets de 4 chiffres héxadécimaux separées par le symbole ":"

0123:0078:9ABC:DEF0:1234:5678:9ABC:DEF0

# MASQUE RESEAU

Le découpage en deux parties est effectué en attribuant certains bits d'une adresse à la partie réseau (net-id) et le reste à la partie machine (host-id).

**EXEMPLE:**

	207.142.131.245 (Adresse IP)
	255.255.255.0 (Masque reseau)

	Ici les trois premiers octet (24 bits) sont utilisés pour adresser le réseau et le dernier octet (8 bits) pour la machine.

	207.142.131.245/255.255.255.0 désigne donc la machine d'adresse 245 sur le réseau d'adresse 207.142.131.0.
	207.142.131.245/255.255.255.0 <=> 207.142.131.245/24 (Notation CIDR, 24 designe le nombre de bit adressé au réseau).

## CLASSE D'ADRESSES

Il existe différents découpages possible que l'on appelle "classes d'adresses". À chacune de ces classes correspond un masque réseau différent :

| Classe | Bits de départ | Début     | Fin             | Notation CIDR | Masque sous-réseau |
|--------|----------------|-----------|-----------------|---------------|--------------------|
| A      | 0---           | 0.0.0.0   | 127.255.255.255 | /8            | 255.0.0.0          |
| B      | 10--           | 128.0.0.0 | 191.255.255.255 | /16           | 255.255.0.0        |
| C      | 110-           | 192.0.0.0 | 223.255.255.255 | /24           | 255.255.255.0      |
| D      | 1110           | 224.0.0.0 | 239.255.255.255 |               |                    |
| E      | 1111           | 240.0.0.0 | 255.255.255.255 |               |                    |

## ADRESSE RESEAU

Une adresse réseau est une adresse IP qui désigne un réseau et non pas une machine de ce réseau. 
Elle est obtenue en plaçant tous les bits de la partie machine à zéro.

Une adresse de diffusion (broadcast) désigne toutes les machines d'un réseau.
Elle est obtenue en plaçant tous les bits de la partie machine à un.

**EXEMPLE:**

| IP (classe)        | Maque         | Adresse réseau | Adresse de diffusion |
|--------------------|---------------|----------------|----------------------|
| 10.10.10.10 (A)    | 255.0.0.0     | 10.0.0.0       | 10.255.255.255       |
| 192.168.150.35 (C) | 255.255.255.0 | 192.168.150.0  | 192.168.150.255      |

Pour éviter les ambiguïtés avec les adresses de réseau et les adresses de diffusion, les adresses "tout à zéro" et "tout à un" sont déconseillées pour désigner des machines sur un réseau.

# SOUS-RESEAUX

Il est possible de découper un réseau en sous-réseaux en utilisant un masque de sous-réseau. 
Un masque de sous-réseau permet d'attribuer des bits supplémentaires à la partie réseau d'une adresse IP.

Supposons que l'on dispose d'une adresse de classe C, elle permet normalement d'adresser 254 machines avec le masque 255.255.255.0.
Il est possible de découper ce réseau en deux sous réseaux de 126 machines avec le masque 255.255.255.128 (128 = 10000000).

# SOUS-RESEAUX DE TAILLE FIXE

On considère le réseau d'adresse 134.214.0.0 et de masque 255.255.0.0. On veut découper ce réseau en 8 sous-réseaux.
Pour chaque sous-réseau, on veut obtenir le masque et l’adresse.

**CALCUL DU MASQUE:**

On veut découper le réseau en 8. Or 8 = 2^3. En conséquence, le masque de chaque sous-réseau est obtenu en ajoutant 3 bits à 1 au masque initial.
L’ancien masque 255.255.0.0 comprend 16 bits à 1 suivis de 16 bits à 0. 
Le nouveau masque comprendra donc 16 + 3 = 19 bits à 1 suivis de 13 bits à 0. 

Il correspond à 255.255.224.0.

**CALCUL DU NET-ID:**

Le net-id de chaque sous-réseau sera constitué de 19 bits :

Les 16 premiers bits seront ceux de l’écriture binaire du préfixe d'adresse 134.214.
Les 3 bits suivants seront constitués du numéro du sous-réseau : 
000 (0), 001 (1), 010 (2), 011 (3), 100 (4), 101 (5), 110 (6) ou 111 (7).

On obtient donc comme adresse pour chaque sous-réseau :

* 134.214.(000 00000).0 => 134.214.0.0
* 134.214.(001 00000).0 => 134.214.32.0
* 134.214.(010 00000).0 => 134.214.64.0
* 134.214.(011 00000).0 => 134.214.96.0
* 134.214.(100 00000).0 => 134.214.128.0
* 134.214.(101 00000).0 => 134.214.160.0
* 134.214.(110 00000).0 => 134.214.192.0
* 134.214.(111 00000).0 => 134.214.224.0

Et on obtient comme adresse de broadcast pour chaque sous-réseau :

* 134.214.(000 00000).255 => 134.214.0.255
* 134.214.(001 00000).255 => 134.214.32.255
* 134.214.(010 00000).255 => 134.214.64.255
* 134.214.(011 00000).255 => 134.214.96.255
* 134.214.(100 00000).255 => 134.214.128.255
* 134.214.(101 00000).255 => 134.214.160.255
* 134.214.(110 00000).255 => 134.214.192.255
* 134.214.(111 00000).255 => 134.214.224.255

# SOUS-RESEAUX DE TAILLE VARIABLES (VSLM)

200.201.202.0/24 (reseau notation point)
1100 1000 . 1100 1001 . 1100 1010 . 00 0 0 0000 (Notation binaire) 

On realise l'adressage avec les masques de sous réseaux à taille variable:

```
                                  (SR1) 200.201.202.0/27 (32-2 hôtes possibles)
                                 /
                 200.201.202.0/26	
                /                \
200.201.202.0/24                  (SR2) 200.201.202.32/27 (32-2 hôtes possibles)
                \
           (SR3) |--200.201.202.64/26 (64-2 hôtes possibles)
                 |							
           (SR4) |--200.201.202.128/26 (64-2 hôtes possibles)
                 |	
           (SR5) |--200.201.202.192/26 (64-2 hôtes possibles)
```

## ADRESSES PRIVEES

Un certain nombre de ces adresses IP sont réservées pour un usage interne aux entreprises, elles ne doivent pas être utilisées sur l'internet où elles ne seront de toute façon pas routées.

Il s’agit des adresses :

* 10.0.0.0 à 10.255.255.255
* 172.16.0.0 à 172.31.255.255
* 192.168.0.0 à 192.168.255.255
* 127.0.0.0 à 127.255.255.255

Les adresses 127.0.0.0 à 127.255.255.255 s’appelle l’adresse de boucle locale et désigne la machine locale (localhost).

# DATAGRAMME IP

Lorsque deux machines communiquent en utilisant le protocole IP, 
elles s'échangent des datagrammes IP qui ont le format ci-dessous : 32 bits (= 4 octets)

	+---------------------------------------------------------------+
	|                    1                   2                   3  |
	|0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1|
	+-------+-------+---------------+-------------------------------+
	|  IPv  |  LgD  | Type service  |        Longueur totale        |
	+-------+-------+---------------+-----+-------------------------+
	|        Identification         | Ind |     Frament offset      |
	+---------------+---------------+-----+-------------------------+
	|  Durée de vie |   Protocole   |      Controle Datagramme      |
	+---------------+---------------+-------------------------------+
	|                        Adresse source                         |
	+---------------------------------------------------------------+
	|                      Adresse destination                      |
	+---------------------------------------------------------------+
	|                     Options + remplissage                     |
	+---------------------------------------------------------------+

**IPv (4 bits) :**
    Version d'IP utilisée. Ici, 4.

**LgD (longueur du l'en-tête(datagramme) ou IHL) (4 bits) :**
    Nombre de mots de 32 bits, soit 4 octets (ou nombre de lignes du schéma). La valeur est comprise entre 5 et 15, car il y a 20 octets minimum et on ne peut dépasser 40 octets d'option (soit en tout, 60 octets).

**Type service ou ToS (Type of Service) (8 bits) :**
    Ce champ permet de distinguer différentes qualités de service différenciant la manière dont les paquets sont traités. Composé de 3 bits de priorité (donc 8 niveaux) et trois indicateurs permettant de différencier le débit, le délai ou la fiabilité.

**Longueur totale (en octets) (16 bits) :**
    Nombre total d'octets du datagramme, en-tête IP comprise. Donc, la valeur maximale est (216)−1 octets.

**Identification (16 bits) :**
    Numéro permettant d'identifier les fragments d'un même paquet.

**Ind (Indicateurs ou Flags) (3 bits) :**
    (Premier bit) actuellement inutilisé.
    (Deuxième bit) DF (Don't Fragment) : lorsque ce bit est positionné à 1, il indique que le paquet ne peut pas être fragmenté. Si le routeur ne peut acheminer ce paquet (taille du paquet supérieure à la MTU), il est alors rejeté.
    (Troisième bit) MF (More Fragments) : quand ce bit est positionné à 1, on sait que ce paquet est un fragment de données et que d'autres doivent suivre. Quand il est à 0, soit le fragment est le dernier, soit le paquet n'a pas été fragmenté.

**Fragment offset (13 bits) :**
    Position du fragment par rapport au paquet de départ, en nombre de mots de 8 octets.

**Durée de vie ou TTL (Time To Live) (8 bits) :**
    Initialisé par l'émetteur, ce champ est décrémenté d'une unité généralement à chaque saut de routeur. Quand TTL = 0, le paquet est abandonné et un message ICMP est envoyé à l'émetteur pour information.

**Protocole (8 bits) :**
    Numéro du protocole au-dessus de la couche réseau : TCP = 6, UDP = 17, ICMP = 1.
    Ce champ permet d'identifier le protocole utilisé par le niveau supérieur :
	
* Internet Control Message Protocol ou ICMP est repéré par les bits 00000001
* Transmission Control Protocol ou TCP par les bits 00000110, soit 06
* User Datagram Protocol ou UDP par les bits 00010001, soit 17 en décimal

**Controle datagramme ou Header Checksum (16 bits) :**
    Complément à un de la somme complémentée à un de tout le contenu de l'en-tête afin de détecter les erreurs de transfert. Si la somme de contrôle est invalide, le paquet est abandonné sans message d'erreur.

**Adresse source (32 bits) :**
    Adresse IP de l'émetteur sur 32 bits.

**Adresse destination (32 bits) :**
    Adresse IP du récepteur 32 bits.

**Options (0 à 40 octets par mots de 4 octets) :**
    Facultatif.

**Remplissage ou Padding :**
    Champ de taille variable comprise entre 0 et 7 bits. Il permet de combler le champ option afin d'obtenir un en-tête IP multiple de 32 bits. La valeur des bits de bourrage est 0. 

# SERVEUR DNS

Le DNS (Domain Name System) est un service qui permet d'effectuer la résolution de noms, c'est à dire d'associer une adresse IP à un FQDN (Full Qualified Domain Name) et inversement.

**EXEMPLE:**

	search info.rmatique.fr nameserver 123.231.111.12
	Veut dire que tout nom simple, par exemple hotel sera recherché (complété) en tant que hotel.info.rmatique.fr
	Ensuite, ayant le nom complet, la requête sera expédiée vers 123.231.111.12
	Le serveur de noms reçoit alors un nom interne ou externe et réagit en fonction de ce qu’il trouve dans sa base.
	S’il ne trouve rien, il doit posséder l’adresse d’au moins un autre serveur de noms (souvent un serveur racine) afin de faire suivre la requête.

* Noter que les requêtes aux serveurs de noms utilisent udp.
* Noter aussi qu’il est indispensable d’avoir l’adresse IP du serveur de noms

# ROUTAGE D'IP

Un routeur est un dispositif relié à au moins deux réseaux, dont le travail est de déterminer le prochain noeud du réseau auquel un paquet de données doit être envoyé. Pour ce faire un routeur utilise une "table de routage".

La table de routage établit la correspondance entre une machine de destination, le prochain routeur et l'interface réseau à utiliser pour suivre ce chemin. Dans le cas où plusieurs chemins sont possibles, on fait appel à des algorithmes spéciaux.

**EXEMPLE:**

| Destination    | Contact | Masque          | Interface |
|----------------|---------|-----------------|-----------|
| 192.36.125.0   | direct  | 255.255.255.192 | xxx0      |
| 192.36.125.64  | direct  | 255.255.255.192 | xxx1      |
| 192.36.125.128 | direct  | 255.255.255.192 | xxx2      |
| 192.36.125.192 | direct  | 255.255.255.192 | xxx3      |
| autre (défaut) | x.y.z.t |       ???       | xxx4      |

**ERREUR ROUTAGE POSSIBLE:**

* Pas de chemin vers l’adresse destination dans sa table de routage,
* L’hôte de destination n’existe pas (détection par le dernier routeur),
* Le réseau par lequel il veut acheminer est en panne ou congestionné,
* Obligation de détruire le datagramme, par exemple, suite à une erreur du code de contrôle, ou à une durée de vie dépassée.

## ALGORITHME TRACEROUTE

``` 
traceroute(Hdest) :
	HdestNonAtteint = vrai
	TTL=0
	tant que (HdestNonAtteint) faire
		TTL++
		expedier(datagramme, Hdest) //demande echo par exemple
		si (reponse ICMP) alors afficher(expediteur erreur ICMP)
		sinon si (reponse Hdest) alors HdestNonAtteint = faux
```

# TCP

TCP, est un protocole de transport fiable, en mode connecté.
Les applications transmettent des flux de données sur une connexion réseau. TCP découpe le flux d’octets en segments dont la taille dépend de la MTU (Maximum transmission unit) du réseau sous-jacent

# UDP

UDP, est un protocole de transport non fiable, en mode non connecté.

* Il est orienté transaction, et donc adapté aux protocoles simples de type requête-réponse tels le DNS ou le NTP.
* Il fournit des datagrammes, utiles pour modéliser d'autres protocoles tel que le tunnelage IP.
* Il est très simple, ce qui le rend adapté pour le bootstrapping ou d'autres usages sans pile de protocoles complète
* Il est dit sans état, ce qui est utile dans des cas où de nombreux clients sont présents, telles les applications de streaming.
* L'absence de délai de retransmission en fait un protocole utile pour les applications en temps réel.
* Il fonctionne efficacement dans des communications unidirectionnelles et est donc adapté pour diffuser des informations comme dans le service discovery (en) ou le protocole d'information de routage.

# SOCKETS:

**LIENS UTILES:**

- [https://fr.wikibooks.org/wiki/R%C3%A9seaux_TCP/IP](https://fr.wikibooks.org/wiki/R%C3%A9seaux_TCP/IP)
- [https://github.com/angrave/SystemProgramming/wiki](https://github.com/angrave/SystemProgramming/wiki)

| TCP                    | UDP                  |
|------------------------|----------------------|
| fiable                 | non fiable           |
| ordre garanti          | ordre non garanti    |
| duplication impossible | duplication possible |
| mode connecté          | mode non connecté    |

**ALLOCATION DES NUMÉROS DE PORT:**

Serveurs sshd 		=> port 22
Serveurs httpd 		=> port 80
Programme personnel => port >1024 (les autres sont déjà utilisé)

**SOCKETS:**

Un canal de communication en réseaux.

```c
           //PF_INET  SOCK_DGRAM       0
int socket(int domain, int type, int protocole); //-1 en cas d'erreur
```

L'exemple ci-dessus crée un socket dans le domaine Ipv4, de type datagramme, avec le protocole par default, UDP.

```c
     //DESCRIPTEUR SOCKETS   POINTEUR VERS L'ADRESSE   LONGUEUR DE L'ADRESSE
int bind(int descripteur, const struct sockaddr *adresse, socklen_t lgAdr);
```
 
**Type generique d'adresse:**

```c
struct sockaddr {
	sa_family_t sa_family;  //famille d'adresse AF_xxx
	char sa_data[14];       //14 octets pour l'IP + port
}
```

Si PF_INET alors struct sockaddr_in : une adresse IPv4 et un port
Si PF_INET6 alors struct sockaddr_in6 : une adresse IPv6 et un port

```c
struct sockaddr_in {
	sa_family_t sin_family;     //famille d'adresse AF_INET
	in_port sin_port;           //numéro de port au format réseau
	struct in_addr sin_addr;    //structure d'adresse IP
}

struct in_addr {
	uint32_t s_addr;            //adresse ip au format réseau
}
```

L'ip et le numéro de port sont au format réseau, les entiers sont au format hôte
une conversion est necessaire (ntohs(), htons(), ntohl(), htonl())

La fonction ci-dessous permet de reutiliser le port directement après la fin du programme.
```c
setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
```
Le code ci-dessous attache la socket à toutes les interfaces réseaux locales via le port 31470.

```c
int dSock = socket(PF_INET, SOCK_STREAM, 0);

struct sockaddr_in ad;
ad.sin_family = AF_INET;
ad.sin_addr.s_addr = INADDR_ANY;
ad.sin_port = htons((short)31470);

int res = bind(dSock, (struct sockaddr*)&ad, sizeof(ad));
```

**fermeture:**

```c
int close(int descripteur);
int shutdown(int descripteur, int comment);
```

comment = SHUT_WR 	=> arret emmision;
comment = SHUT_RDWR => arret emmision et reception;

**COMMUNICATION UDP:**

```c
ssize_t recvfrom(int descripteur,				//descripteur de socket
				 const void *msg,				//pointeur pour stocker le msg reçu
				 size_t lg,						//nombre max d'octets attendu
				 int flags,						//option de réceptions 0 par defaut
				 const struct sockaddr *adrExp,	//pointeur vers l'adresse de l'expediteur
				 sockelen_t *lgAdr);			//longueur de l'adresse

ssize_t sendto(int descripteur,					//descripteur de socket
			   const void *msg,					//pointeur vers le msg à envoyer
			   size_t lg,						//nombre d'octets du msg
			   int flags,						//option d'envoi 0 par defaut
			   const struct sockaddr *adrExp,	//pointeur vers l'adresse du destinataire
			   sockelen_t *lgAdr);	//longueur de l'adresse
```

**COMMUNICATION TCP:**

Passer la socket en mode attente de connexion (serveur):

```c
int listen(int descripteur, int nbMaxEnAttente); //nombre max de connexion en attente.
```

**Demander la connexion a un serveur:**

```c
int connect(int descr, const struct sockaddr *adServ, socklen_t lgAdr);
```

**Exemple:**

Envoie une demande de connexion de la socket du clien dS au serveur, via la socket du serveur dont l'IP est 197.50.51.10 et le numéro de port 34567.
```c
struct sockaddr_in adServ; 

adServ.sin_family = AF INET;
adServ.sin_port = htons(34567);

int res = inet_pton(AF INET, ”197.50.51.10”, &(adServ.sin_addr));
socklen t lgA = sizeof(struct sockaddr_in);

res = connect(dS, (struct sockaddr *)&adServ, lgA);
```

**Accepter une demande de connexion d'un client:**

```c
int accept(int descr, struct sockaddr *adrClient, socklen_t lgAdr);
```

**Recevoir/Envoyer un message tcp:**

```c
ssize_t recv(int descripteur, const void *msg, size_t lg, int flags);
ssize_t send(int descripteur, const void *msg, size_t lg, int flags);
```

**ADRESSES ET NOM D'HOTE:**

La structure suivante représente le liens entre une adresse et un nom d'hote.
```c
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>


struct addrinfo {
    int              ai_flags;
    int              ai_family;		//Famille d'adresse préféré (IPv4/IPv6)
    int              ai_socktype;	//Type de socket préféré
    int              ai_protocol;	//Protocol des adresse de socket renvoyé (0 = tout)
    socklen_t        ai_addrlen;	//Longueur de l'adresse
    struct sockaddr *ai_addr;		//Addresse correspondante
    char            *ai_canonname;	//Nom canonique
    struct addrinfo *ai_next;		//La structure peut former une liste chainée
};
```
La fonction suivante convertie un nom d'hote ou une adresse IP sous forme de chaine de charactère, en une list chainée de addrinfo.

```c
int getaddrinfo(const char *node,
                const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);

void freeaddrinfo(struct addrinfo *res);
```

La fonction suivante fais l'inverse, elle convertie la representation binaire d'une addresse en un nom d'hote ou en une addresse IP textuel si aucun nom n'est trouvé.

```c
int getnameinfo(const struct sockaddr *sa, socklen_t salen,
                char *host, size_t hostlen,
                char *serv, size_t servlen,
                int flags);
```