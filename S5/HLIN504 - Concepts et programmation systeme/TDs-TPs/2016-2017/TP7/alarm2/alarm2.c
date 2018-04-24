#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sig_handler(int);

struct sigaction action;

int main() {
    action.sa_handler = sig_handler;
    action.sa_flags = SA_RESTART;
    sigaction(SIGALRM , &action , NULL);
    int answer;
    
    printf("2 + 2 = ");
    alarm(3);
    scanf("%i" , &answer);
    alarm(0);
    
    if(answer == 4)
        printf("Well done!\n");
    else
        printf("Go back to school\n");
    return 0;
}

void sig_handler(int sig) {
    static int cpt = 1;
    switch(cpt) {
        case 1 :
            printf("\nHurry up fam!\n");
            cpt++;
            alarm(3);
            return;
            break;
        case 2 :
            printf("Too late!\n");
            exit(1);
            break;
    }
}
