#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc , char ** argv) {
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    
    if(sock == -1){
        printf("error opening socket\n");
        return -1;
    }
    
    sin.sin_port = htons(0);
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_family = AF_INET;
    
    if(bind(sock, (struct sockaddr *)&sin , sizeof(sin)) == -1){
        printf("error binding socket\n");
        return -1;
    }
    
    getsockname(sock, (struct sockaddr *)&sin, &len);
    printf("%s : %d\n", inet_ntoa(sin.sin_addr) , ntohs(sin.sin_port));
    return 0;
}
