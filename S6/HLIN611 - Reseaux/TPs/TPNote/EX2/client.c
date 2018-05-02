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

int tcp_send_msg(int sock_fd, const char* str, int str_len){

	/* Envoi de la taille du msg */
	CHECK(send(sock_fd, &str_len, sizeof(int), 0), return -1)

	/* Envoi du msg */
	CHECK(send(sock_fd, str, str_len, 0), return -1)

	return 0;
}

char* tcp_recv_msg(int sock_fd, int* str_len){

    int len = 0;
    char* str = NULL;
    /* Reception de la taille du msg */
    CHECK(recv(sock_fd, str_len, sizeof(int), 0), return NULL)

    str = malloc(((*str_len) + 1) * sizeof(char));
    /* Reception du msg */
    while(*str_len > len){
        len += recv(sock_fd, str, *str_len, 0); 
    }

    str[*str_len] = '\0';

    return str;
}

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
    hints.ai_socktype =  SOCK_STREAM; // TCP
    hints.ai_flags =  AI_PASSIVE;

    int dest_fd = create_socket(addr, port, &hints, &res);
    CHECK(dest_fd, exit(1))

	printf("Connexion a la socket...\n");

    CHECK(connect(dest_fd, res->ai_addr, res->ai_addrlen), exit(2));

    printf("Echange de données en cours...\n");

	strncpy(buf, getlogin(), 256);

	tcp_send_msg(dest_fd, buf, strlen(buf));

	printf("Envoyer : %s\n", buf);

	char* resp = NULL;
	int resp_len = 0;

	resp = tcp_recv_msg(dest_fd, &resp_len);

	printf("Reçu : %s\n", resp);

	free(resp);
	freeaddrinfo(res);
	close(dest_fd);

	return 0;
}