#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc , char * argv[]) {
    struct sockaddr_in si_me , si_distant;
    int sock_me = socket(PF_INET , SOCK_STREAM , 0),
    sock_dist,
    send_len,
    recv_len;
    socklen_t sock_me_len = sizeof(struct sockaddr_in),
    sock_dist_len = sizeof(struct sockaddr_in);
    
    if(-1 == sock_me) {
        fprintf(stderr , "Error while creating socket\n");
        exit(1);
    }
    
    si_me.sin_addr.s_addr = htons(INADDR_ANY);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(31469);
    
    if(-1 == bind(sock_me , (struct sockaddr *)&si_me , sock_me_len)) {
        fprintf(stderr , "Error while binding socket\n");
        exit(2);
    }
    getsockname(sock_me , (struct sockaddr *)&si_me , &sock_me_len);
    printf("Server running on %s:%d\n", inet_ntoa(*(struct in_addr *)&(si_me.sin_addr.s_addr)), ntohs(si_me.sin_port));
    
    if(-1 == listen(sock_me , 5)) {
        fprintf(stderr , "Error while listening\n");
        exit(3);
    }
    
    while(1) {
        char recv_buffer[1024], send_buffer[1024] = "Hey there, ";
        sock_dist = accept(sock_me , (struct sockaddr *)&si_distant , &sock_dist_len);
        getsockname(sock_dist , (struct sockaddr *)&si_distant , &sock_dist_len);
        getpeername(sock_dist , (struct sockaddr *)&si_distant , &sock_dist_len);
        printf("Client running on %s:%d\n", inet_ntoa(*(struct in_addr *)&(si_distant.sin_addr.s_addr)), ntohs(si_distant.sin_port));

        if(-1 == (recv_len = read(sock_dist , recv_buffer , 1024))) {
            fprintf(stderr , "Error while receiving message\n");
            exit(3);
        }
        
        strcat(send_buffer , recv_buffer);
        if(-1 == (send_len = write(sock_dist , send_buffer , strlen(send_buffer)))) {
            fprintf(stderr , "Error while sending message\n");
            exit(4);
        }
    }
    return 0;   
}