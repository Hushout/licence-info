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

    int error;
    int sock_fd;

    error = getaddrinfo(addr, port, hints, res);
    CHECK_GAI(error, return -1)

    sock_fd = socket((*res)->ai_family, (*res)->ai_socktype, (*res)->ai_protocol);
    CHECK(sock_fd, return -1)

    return sock_fd;
}

int bind_socket(int sock_fd, struct addrinfo** res);

int main(int argc, char const *argv[])
{	
	const char* addr;
	const char* port;

	char buf[256] = "";

	if(argc < 3){
		fprintf(stderr, "Usage %s <ADRESS> <PORT>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	addr = argv[1];
	port = argv[2];

	printf("Creation de la socket vers l'hote %s et le port %s...\n", addr, port);

	struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype =  SOCK_DGRAM; // UDP
    hints.ai_flags =  AI_PASSIVE;

    int dest_fd = create_socket(addr, port, &hints, &res);
    CHECK(dest_fd, exit(1))

    printf("Echange de données en cours...\n");

    struct sockaddr_storage sender;
	socklen_t sendsize = sizeof(sender);

	strncpy(buf, getlogin(), 256);

	sendto(dest_fd, buf, sizeof(buf) - 1, 0, res->ai_addr, res->ai_addrlen);

	printf("Envoyer : %s\n", buf);

	recvfrom(dest_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&sender, &sendsize);

	printf("Reçu : %s\n", buf);

	freeaddrinfo(res);
	close(dest_fd);
	return 0;
}