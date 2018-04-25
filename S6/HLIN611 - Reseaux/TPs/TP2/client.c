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
	int n = -1;
	const char* adr;
	short port = -1;

	if(argc < 4){
		fprintf(stderr, "Usage %s <NUMBER> <ADRESS> <PORT>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	adr = argv[2];
	port = atoi(argv[3]);

	printf("Création de la socket...\n");

	int sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
	CHECK_FD(sock_fd)

	struct sockaddr_in dest_adr;

	dest_adr.sin_family = AF_INET;
	dest_adr.sin_port = htons(port);

   	//Convertion de L'IP (chaine de charactère) en adresse network.
	int error = inet_pton(AF_INET, adr, &(dest_adr.sin_addr));
	CHECK_ERROR(error)

	//Permet de réutilliser le port directement après la fin du programme
    int optval = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

	error = bind(sock_fd, (struct sockaddr*)&dest_adr, sizeof(dest_adr));
	CHECK_ERROR(error)

	sendto(sock_fd, &n, sizeof(n), 0, (struct sockaddr *)&dest_adr, sizeof(dest_adr));

	close(sock_fd);
	return 0;
}