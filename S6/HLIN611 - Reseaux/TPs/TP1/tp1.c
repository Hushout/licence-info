#include "stdlib.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
	if(argc < 2 || argc > 3){
		fprintf(stden, "%s hostname [options]", argv[0]);
		return 1;
	}
	
	char* h = argv[1];
	char* s = NULL;

	if(argc == 3){s = argv[2]}

	struct addrinfo* resultat;

	int error = getaddrinfo("umontpellier.fr", "truc");
	return 0;
}