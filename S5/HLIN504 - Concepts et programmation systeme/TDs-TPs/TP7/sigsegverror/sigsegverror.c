#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

void sig_handler(int);

int main() {
    struct sigaction action;
    action.sa_handler = sig_handler;
    sigaction(SIGSEGV , &action , NULL);
    int * p = NULL;
    
    printf("%d\n" , *p);
}

void sig_handler(int sig) {
    printf("Received signal %d\n" , sig);
    printf("errno : %d\nmessage : %s\n", errno , strerror(errno));
    exit(1);
}