#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void sieve(int *);

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
            sieve(_pipe);
            exit(0);
            break;
        default :
            close(_pipe[0]);
            for(int i = 2 ; i <= limit ; i++)
                write(_pipe[1] , (void *)&i , sizeof(int));
            close(_pipe[1]);
            wait(0);
            break;
    }
    return 0;
}

void sieve(int * in) {
    pid_t child;
    int prime;
    int out[2];

    if(-1 == close(in[1])) {
        printf("Error while closing\n");
        exit(3);
    }
    if(read(in[0] , (void *)&prime , sizeof(int)) != sizeof(int)) {
        close(in[0]);
        return;
    }
    printf("%d\n" , prime);
    if(-1 == pipe(out)) {
        printf("Error while creating pipe\n");
        exit(1);
    }
    
    switch(child = fork()) {
        case -1 :
            printf("There was an error while forking\n");
            exit(2);
            break;
        case 0 :
            close(in[0]);
            sieve(out);
            exit(0);
            break;
        default :
            close(out[0]);
            int i;
            while(read(in[0] , (void *)&i , sizeof(int)) == sizeof(int))
                if(i % prime)
                    write(out[1] , (void *)&i , sizeof(int));
            close(in[0]);
            close(out[1]);
            wait(0);
            return;
            break;
    }
}