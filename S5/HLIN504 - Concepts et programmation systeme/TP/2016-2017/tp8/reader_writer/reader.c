#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc , char * argv[]) {
    int f_pipe,
    counter = 1024,
    nb_char;
    char buffer[counter + 1];
    
    if(argc != 2) {
        printf("You must run this program with exactly one argument!\n");
        exit(1);
    }
    if(-1 == mkfifo(argv[1] , S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH) && errno != EEXIST)
        perror("Error with fifo, continuing\n");
    else
        chmod(argv[1] , 0666);
    if(-1 == (f_pipe = open(argv[1] , O_RDONLY))) {
        printf("Error while opening pipe\n");
        exit(2);
    }
    
    while(0 != (nb_char = read(f_pipe , buffer , counter))) {
        buffer[nb_char] = '\0';
        printf("%s\n" , buffer);
    }
    unlink(argv[1]);
    return 0;
}