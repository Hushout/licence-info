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
	const char* port;

	if(argc < 2){
		fprintf(stderr, "Usage %s <PORT>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = argv[1];

    printf("Création de la socket...\n");

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET; // IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;

    int sock_fd = create_socket(NULL, port, &hints, &res);
    CHECK(sock_fd, exit(1))
    
    printf("Nommage de la socket...\n");

	CHECK(bind(sock_fd, res->ai_addr, res->ai_addrlen), exit(2))

    freeaddrinfo(res);

    CHECK_GAI(listen(sock_fd, 10), exit(3))

	printf("Serveur TCP en attente de connexion...\n");
	printf("PORT : %s\n", port);

    int client_fd = accept(sock_fd, NULL, NULL);
    CHECK(client_fd, exit(4))

    printf("Connexion en cours avec le client %d\n", client_fd);

    char* msg = NULL;
    int msg_len = 0;

    msg = tcp_recv_msg(client_fd, &msg_len);

    printf("Reçu : %s\n", msg);
   
    char resp[256] = "";

    snprintf(resp, 256, "%s bien reçu !", msg);

    tcp_send_msg(client_fd, resp, strlen(resp));
    
    printf("Envoyer : %s\n", resp);

    free(msg);
    close(client_fd);
    close(sock_fd);

	return 0;
}
