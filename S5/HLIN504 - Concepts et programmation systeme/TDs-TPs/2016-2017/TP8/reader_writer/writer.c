#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void sig_handler(int);

char _pipe_name[1024];

int main(int argc , char * argv[]) {
    struct sigaction action;
    action.sa_handler = sig_handler;
    sigaction(SIGPIPE , &action , NULL);
    int f_pipe,
    counter = 1024;
    char buffer[counter + 1];
    char * res;
    
    if(argc != 2) {
        printf("You must run this program with exactly one argument!\n");
        exit(1);
    }
    if(-1 == mkfifo(argv[1] , S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH) && errno != EEXIST)
        perror("Error with fifo, continuing\n");
    else
        chmod(argv[1] , 0666);
    if(-1 == (f_pipe = open(argv[1] , O_WRONLY))) {
        printf("Error while opening pipe\n");
        exit(2);
    }
    strcpy(argv[1] , _pipe_name);
    printf(">");
    res = fgets(buffer , counter , stdin);
    while(res) {
        write(f_pipe , buffer , strlen(buffer));
        printf(">");
        res = fgets(buffer , counter , stdin);
    }
    return 0;
}

void sig_handler(int sig) {
    unlink(_pipe_name);
    exit(3);
}