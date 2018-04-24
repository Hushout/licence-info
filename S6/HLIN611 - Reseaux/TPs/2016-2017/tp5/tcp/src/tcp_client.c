#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pwd.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc , char * argv[]) {
    struct passwd * pwd = getpwuid(0);
    struct sockaddr_in si_me , si_distant;
    int sock_me = socket(PF_INET , SOCK_STREAM , 0),
    sock_dist,
    send_len,
    recv_len;
    socklen_t sock_me_len = sizeof(struct sockaddr_in),
    sock_dist_len = sizeof(struct sockaddr_in);
    char buffer[1024];
    
    if(-1 == sock_me) {
        fprintf(stderr , "Error while creating socket\n");
        exit(1);
    }
    
    si_me.sin_addr.s_addr = htons(INADDR_ANY);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(0);
    
    si_distant.sin_addr.s_addr = htons(INADDR_ANY);
    si_distant.sin_family = AF_INET;
    si_distant.sin_port = htons(31469);
    
    if(-1 == bind(sock_me , (struct sockaddr *)&si_me , sock_me_len)) {
        fprintf(stderr , "Error while binding socket\n");
        exit(2);
    }
    getsockname(sock_me , (struct sockaddr *)&si_me , &sock_me_len);
    printf("Client running on %s:%d\n", inet_ntoa(*(struct in_addr *)&(si_me.sin_addr.s_addr)), ntohs(si_me.sin_port));
    
    if(-1 == connect(sock_me , (struct sockaddr *)&si_distant , sock_dist_len)) {
        fprintf(stderr , "Error while connecting to server\n");
        exit(3);
    }
    
    strcpy(buffer , pwd->pw_name);
    if(-1 == (send_len = write(sock_me , (void *)buffer , strlen(buffer)))) {
        fprintf(stderr , "Error while sending message\n");
        exit(4);
    }
    
    if(-1 == (recv_len = read(sock_me , (void *)buffer , 1024))) {
        fprintf(stderr , "Error while receiving message\n");
        exit(5);
    }
    printf("%s\n", buffer);
    
    return 0;
}