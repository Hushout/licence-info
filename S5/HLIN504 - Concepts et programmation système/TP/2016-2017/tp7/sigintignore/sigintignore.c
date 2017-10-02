#include <stdio.h>
#include <signal.h>

void sig_handler(int sig);

int main() {
    struct sigaction action;
    action.sa_handler = SIG_IGN;
    sigaction(SIGINT , &action , NULL);
    
    printf("Program looping indefinitely\n");
    
    while(1);
}
