#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void count(int *);

int main(int argc , char * argv[]) {
    int _pipe[2];
    int fd;
    int child;
    char c;
    
    if(argc != 2) {
        printf("You must run this program with exactly one argument!\n");
        exit(1);
    }
    if(-1 == (fd = open(argv[1] , O_RDONLY))) {
        printf("Can't open file %s\n" , argv[1]);
        exit(2);
    }
    if(-1 == pipe(_pipe)) {
        printf("Error while creating pipe\n");
        exit(3);
    }
    switch(child = fork()) {
        case -1 :
            printf("Error while creating fork\n");
            exit(4);
            break;
        case 0 :
            count(_pipe);
            exit(0);
            break;
        default :
            close(_pipe[0]);
            while(read(fd , &c , sizeof(char)) == sizeof(char))
                write(_pipe[1] , (void *)&c , sizeof(char));
            close(_pipe[1]);
            wait(0);
            break;
    }
    return 0;
}

void count(int * in) {
    int out[2];
    int child;
    int nb_char = 0;
    char c , c2;
    
    if(-1 == close(in[1])) {
        printf("Error while closing pipe\n");
        exit(5);
    }
    
    if(read(in[0] , &c , sizeof(c)) == 0) {
        close(in[0]);
        return;
    }
    nb_char++;
    
    if(-1 == pipe(out)) {
        printf("Error while creating pipe\n");
        exit(3);
    }
    
    switch(child = fork()) {
        case -1 :
            printf("Error while creating fork\n");
            exit(4);
            break;
        case 0 :
            close(in[0]);
            count(out);
            exit(0);
            break;
        default :
            close(out[0]);
            while(read(in[0] , (void *)&c2 , sizeof(char)) == sizeof(char)) {
                if(c != c2)
                    write(out[1] , (void *)&c2 , sizeof(char));
                else nb_char++;
            }
            close(in[0]);
            close(out[1]);
            printf("%c : %d\n" , c , nb_char);
            wait(0);
            break;
    }
    return;
}