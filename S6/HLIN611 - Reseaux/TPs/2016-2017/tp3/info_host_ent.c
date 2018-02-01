#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc , char ** argv) {
    struct hostent * host = gethostbyname(argv[1]);
    int i = 0;
    
    if(!host) {
        printf("Machine non trouvée\n");
        return 1;
    }
    printf("Nom : %s\n" , host->h_name);
    printf("Liste des alias : \n");
    while(host->h_aliases[i]) {
        printf("%s " , host->h_aliases[i]);
        i++;
    }
    printf("Type d'adresse : %d\n" , host->h_addrtype);
    printf("Longueur d'adresse : %d\n" , host->h_length);
    i = 0;
    printf("Liste d'adresses : \n");
    while(host->h_addr_list[i]) {
        struct in_addr * addr = (struct in_addr *)host->h_addr_list[i];
        printf("%s\n" , inet_ntoa(*addr));
        i++;
    }
    return 0; 
}
