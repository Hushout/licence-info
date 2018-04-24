#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc , char * argv[]) {
    int block;
    if(argc != 2) {
        printf("You must run this program with exactly one argument!\n");
        exit(1);
    }
    if(0 >= (block = atoi(argv[1]))) {
        printf("You must enter an integer value as argument!\n");
        exit(2);
    }
    char message[block];
    int _pipe[2];
    if(0 > (pipe(_pipe))) {
        printf("Error while creating pipe\n");
        exit(3);
    }
    for(int i = 1 ; i != 0 ; i++) {
        write(_pipe[1] , message , block);
        printf("%d bytes\n" , i * block);
    }
    return 0;
}