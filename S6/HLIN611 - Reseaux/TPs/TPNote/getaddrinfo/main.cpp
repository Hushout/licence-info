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

void printInfo(struct addrinfo *addr);

int main(int argc, char const *argv[])
{
	struct addrinfo hints, *res = NULL, *rp = NULL;

	if(argc != 2){
		fprintf(stderr, "Usage : %s <HOSTNAME>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Initialise tous les elements de la structure à 0 */
	memset(&hints, 0, sizeof(struct addrinfo));

	/* On prends seulement les IPv4 */
	hints.ai_family = AF_INET;    	
    
    int error = getaddrinfo(argv[1], NULL, &hints, &res);

    CHECK_GAI_ERROR(error);

	for(rp = res; rp != NULL; rp = rp->ai_next) {
		printInfo(rp);
	}

	freeaddrinfo(res);

	return 0;
}

void printInfo(struct addrinfo *addr){

	int errorhost, errorname;
	char host[256], officialname[256];
	char socktype[256] = "";

	errorhost = getnameinfo(addr->ai_addr, addr->ai_addrlen, host, sizeof(char) * 256, NULL, 0, NI_NUMERICHOST);
	errorname = getnameinfo(addr->ai_addr, addr->ai_addrlen, officialname, sizeof(char) * 256, NULL, 0, NI_NUMERICSERV);

	CHECK_GAI_ERROR(errorhost);
	CHECK_GAI_ERROR(errorname);

	switch(addr->ai_socktype){
		case SOCK_STREAM:
			strcpy(socktype, "STREAM");
			break;
		case SOCK_DGRAM:
			strcpy(socktype, "DGRAM ");
			break;
		default:
			strcpy(socktype, "RAW   ");
			break;
	}

	printf("%s\t%s\t%s\n", host, socktype, officialname);
}
