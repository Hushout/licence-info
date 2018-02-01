#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void sig_handler(int);

const int BUF_LEN = 10;
struct sigaction action;

int main(int argc , char * argv[]) {
    action.sa_handler = sig_handler;
    sigaction(SIGALRM , &action , NULL);
    struct hostent * ent;
    struct sockaddr_in si_me , si_distant;
    socklen_t sock_len = sizeof(si_me);
    char buffer_recv[BUF_LEN] , buffer_send[BUF_LEN];
    int sock_fd = socket(PF_INET , SOCK_DGRAM , 0),
    rcv_len = 0,
    snd_len = 0;
    
    if(argc != 2) {
        fprintf(stderr , "You must run this program with exactly one argument!\n");
        exit(1);
    }
    ent = gethostbyname(argv[1]);
    printf("%s\n" , inet_ntoa(*(struct in_addr *)ent->h_addr));
    
    if(-1 == sock_fd) {
        fprintf(stderr , "Error while creating socket\n");
        exit(2);
    }
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(0);
    memcpy(&si_distant.sin_addr, ent->h_addr_list[0], ent->h_length);
    si_distant.sin_family = AF_INET;
    si_distant.sin_port = htons(31470);
    
    if(-1 == bind(sock_fd , (struct sockaddr *)&si_me , sock_len)) {
        fprintf(stderr , "Error while binding socket\n");
        exit(3);
    }
    getsockname(sock_fd , (struct sockaddr *)&si_me , &sock_len);
    printf("%s : %d\n", inet_ntoa(si_distant.sin_addr) , ntohs(si_distant.sin_port));
    strcpy(buffer_send , "apprifix");
    
    if(-1 == (snd_len = sendto(sock_fd , buffer_send , strlen(buffer_send) , 0 , (struct sockaddr *)&si_distant , sock_len))) {
        fprintf(stderr , "Error while sending message\n");
        exit(4);
    }
    printf("Sent %d characters\n" , snd_len);

    alarm(5);
    if(-1 == (rcv_len = recvfrom(sock_fd , buffer_recv , BUF_LEN , 0 , (struct sockaddr *)&si_distant , &sock_len))) {
        fprintf(stderr , "Error while sending message\n");
        exit(4);
    }
    alarm(0);
    printf("Received %d characters : %s\n" , rcv_len , buffer_recv);
    return 0;
}

void sig_handler(int sig) {
    printf("No response, the packets were probably lost\n");
    exit(5);
}