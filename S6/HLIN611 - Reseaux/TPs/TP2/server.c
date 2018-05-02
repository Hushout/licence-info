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

int main(int argc, char const *argv[])
{
	const char* port;

	if(argc < 2){
		fprintf(stderr, "Usage %s <PORT>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = argv[1];

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET; // INET for IPv4
    hints.ai_socktype =  SOCK_DGRAM;
    hints.ai_flags =  AI_PASSIVE;

    printf("Accès à l'adresse liée au port %s...\n", port);

    //Pas besoin de spécifier l'hote comme nous créons un serveur.
	getaddrinfo(NULL, port, &hints, &res);

	printf("Création de la socket...\n");

	int sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	CHECK_FD(sock_fd)

	//Permet de réutilliser le port directement après la fin du programme
    //int optval = 1;
   	//setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

   	char address[256] = "";
   	//Convertion de l'adresse IP en chaine de charactère.
	inet_ntop(AF_INET, &((struct sockaddr_in*)res->ai_addr)->sin_addr, address, sizeof(address));

	printf("Affectation de l'adresse %s à la socket...\n", address);

	int error = bind(sock_fd, res->ai_addr, res->ai_addrlen);
	CHECK_ERROR(error)

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

	printf("Serveur UDP en attente de connexion...\n");
	printf("IP : %s, PORT : %s\n", address, port);

    while(1){
    	int n = -1;
        ssize_t byte_count = recvfrom(sock_fd, &n, sizeof(&n), 0, (struct sockaddr*)&addr, &addrlen);

        printf("%d\n", n);
    }

    close(sock_fd);

	return 0;
}
