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
    struct sockaddr_in si_me, si_distant;
    socklen_t len = sizeof(si_me);
    char buffer[10];
    int sock_me = socket(PF_INET, SOCK_DGRAM, 0),
    buf_len = sizeof(buffer),
    recv_len = 0;
    pid_t child;
    
    if(sock_me == -1){
        printf("error opening socket\n");
        exit(1);
    }
    
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons((short)31469);
    
    if(bind(sock_me, (struct sockaddr *)&si_me , sizeof(si_me)) == -1){
        printf("error binding socket\n");
        exit(2);
    }
    
    getsockname(sock_me, (struct sockaddr *)&si_me, &len);
    printf("%s : %d\n", inet_ntoa(si_me.sin_addr) , ntohs(si_me.sin_port));
    
    while(1) {
        fflush(stdout);
        recv_len = (recvfrom(sock_me , buffer , buf_len - 1 , 0 , (struct sockaddr *)&si_distant , &len));
        switch(child = fork()) {
            case -1 :
                printf("Fork error\n");
                exit(3);
                break;
                
            case 0 :
                if(recv_len == 0) {
                    printf("Error while receiving message\n");
                    exit(4);
                }
                buffer[recv_len] = '\0';
                printf("%s\n" , buffer);
                printf("%d characters received\n" , recv_len);
                if(-1 ==(recv_len = (sendto(sock_me , buffer , strlen(buffer) , 0 , (struct sockaddr *)&si_distant , len)))) {
                    printf("Error while sending message\n");
                    exit(5);
                }
                printf("%d characters sent\n" , recv_len);
                exit(0);
                break;
                
            default : break;
        }
    }
    close(sock_me);
    return 0;
}
