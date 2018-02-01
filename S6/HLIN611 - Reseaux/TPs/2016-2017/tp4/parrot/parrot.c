#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc , char ** argv) {
    struct sockaddr_in si_distant , si_me;
    socklen_t len = sizeof(si_distant);
    char buffer[10];
    int sock_me = socket(PF_INET , SOCK_DGRAM , 0),
    buf_len = sizeof(buffer),
    recv_len = 0,
    send_len = 0;

    if(sock_me == -1){
        printf("error opening socket\n");
        exit(1);
    }
    
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons((short)31470);
    
    si_distant.sin_addr.s_addr = atoi("0.0.0.0");
    si_distant.sin_family = AF_INET;
    si_distant.sin_port = htons((short)31469);
    
    if(bind(sock_me, (struct sockaddr *)&si_me , len) == -1){
        printf("error binding socket\n");
        exit(2);
    }
    
    getsockname(sock_me, (struct sockaddr *)&si_me, &len);
    printf("%s : %d\n", inet_ntoa(si_distant.sin_addr) , ntohs(si_distant.sin_port));
    
    while(1) {
        printf("Type your message\n");
        scanf("%s" , buffer);
        if(-1 == (send_len = sendto(sock_me , buffer , strlen(buffer) , 0 , (struct sockaddr *)&si_distant , len))) {
            printf("Error while sending message\n");
            exit(4);
        }
        printf("%d characters sent\n" , send_len);
    
        if(-1 == (recv_len = recvfrom(sock_me , buffer , buf_len - 1 , 0 , (struct sockaddr *)&si_distant , &len))) {
            printf("Error while receiving message\n");
            exit(5);
        }
        buffer[recv_len] = '\0';
        printf("%s\n" , buffer);
        printf("%d characters received\n" , recv_len);
    }
    close(sock_me);
    return 0;
}