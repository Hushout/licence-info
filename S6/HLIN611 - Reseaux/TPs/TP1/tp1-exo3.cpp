#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;

void printInfo(struct addrinfo *addr);

int main(int argc, char const *argv[])
{
	struct addrinfo hints, *res = NULL, *rp = NULL;

	if(argc != 2){
		cout <<  "Usage : " << argv[0] << " <HOSTNAME>" << endl;
		exit(EXIT_FAILURE);
	}

	/* Initialise tous les elements de la structure à 0 */
	memset(&hints, 0, sizeof(struct addrinfo));
	/* On prends seulement les IPv4 */
	hints.ai_family = AF_INET;    	
    
    int error = getaddrinfo(argv[1], NULL, &hints, &res);

	if (error) {
		cerr << "getaddrinfo: " <<  gai_strerror(error) << endl;
		exit(EXIT_FAILURE);
	}

	for(rp = res; rp != NULL; rp = rp->ai_next) {
		printInfo(rp);
	}

	freeaddrinfo(res);

	return 0;
}

void printInfo(struct addrinfo *addr){

	int errorhost, errorname;
	char host[256], officialname[256];
	string socktype;

	errorhost = getnameinfo(addr->ai_addr, addr->ai_addrlen, host, sizeof(char) * 256, NULL, 0, NI_NUMERICHOST);
	errorname = getnameinfo(addr->ai_addr, addr->ai_addrlen, officialname, sizeof(char) * 256, NULL, 0, NI_NUMERICSERV);

	if(errorhost){
		cerr << "getnameinfo: " <<  gai_strerror(errorhost) << endl;
		exit(EXIT_FAILURE);
	}

	if(errorname){
		cerr << "getnameinfo: " <<  gai_strerror(errorname) << endl;
		exit(EXIT_FAILURE);
	}

	switch(addr->ai_socktype){
		case SOCK_STREAM:
			socktype = "STREAM";
			break;
		case SOCK_DGRAM:
			socktype = "DGRAM";
			break;
		default:
			socktype = "RAW";
			break;
	}

	cout << left << host << "    " << setw(9) << socktype << " " << officialname << endl;
}
