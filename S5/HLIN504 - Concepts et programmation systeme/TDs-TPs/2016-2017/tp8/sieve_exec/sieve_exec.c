#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc , char * argv[]) {
    int limit;
    int _pipe[2];
    pid_t child;
    
    if(argc != 2) {
        printf("You must run this program with exactly one argument!\n");
        exit(1);
    }
    if(2 > (limit = atoi(argv[1]))) {
        printf("You must enter an integer >= 2 as argument!\n");
        exit(2);
    }
    if(-1 == (pipe(_pipe))) {
        printf("Error while creating pipe\n");
        exit(3);
    }
    
    switch(child = fork()) {
        case -1 :
            printf("There was an error while forking\n");
            exit(4);
            break;
        case 0 :
            close(_pipe[1]);
            dup2(_pipe[0] , 0);
            close(_pipe[0]);
            execl("fsieve" , "fsieve" , NULL);
            break;
        default :
            close(_pipe[0]);
            for(int i = 2 ; i <= limit ; i++)
                write(_pipe[1] , (void *)&i , sizeof(int));
            close(_pipe[1]);
            wait(0);
            return 0;
            break;
    }
    return 0;
}