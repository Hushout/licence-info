#include <stdio.h>
#include <signal.h>

void sig_handler(int sig);

int main() {
    struct sigaction action;
    action.sa_handler = sig_handler;
    sigaction(SIGINT , &action , NULL);
    
    printf("Program looping indefinitely\n");
    
    while(1);
}

void sig_handler(int sig) {
    printf("\nSignal received : %d\n" , sig);
}