#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include "check.h" //Verifications d'erreurs


int create_socket(const char* addr, const char* port, struct addrinfo* hints, struct addrinfo** res){

    int sock_fd;

    CHECK_GAI(getaddrinfo(addr, port, hints, res), return -1)

    sock_fd = socket((*res)->ai_family, (*res)->ai_socktype, (*res)->ai_protocol);
    CHECK(sock_fd, return -1)

    return sock_fd;
}

int main(int argc, char const *argv[])
{
    int sock_fd = -1;
	const char* port;

    char buf[256] = "";

	if(argc < 2){
		fprintf(stderr, "Usage %s <PORT>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = argv[1];

    printf("Creation de la socket via le port %s...\n", port);

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET; // INET for IPv4
    hints.ai_socktype =  SOCK_DGRAM;
    hints.ai_flags =  AI_PASSIVE;

    sock_fd = create_socket(NULL, port, &hints, &res);
    CHECK(sock_fd, exit(1));

    CHECK(bind(sock_fd, res->ai_addr, res->ai_addrlen), exit(2))

    freeaddrinfo(res);

	printf("Serveur UDP en attente de connexion...\n");
	printf("PORT : %s\n", port);

    struct sockaddr_storage sender;
    socklen_t sendsize = sizeof(sender);

    while(1){
        char resp[256] = "";

        recvfrom(sock_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&sender, &sendsize);
        printf("Reçu : %s\n", buf);

        snprintf(resp, 256, "Bonjour %s !", buf);

        sendto(sock_fd, resp, sizeof(resp) - 1, 0, (struct sockaddr*)&sender, sendsize);
        printf("Envoyer : %s\n", resp);
    }

    close(sock_fd);

	return 0;
}
