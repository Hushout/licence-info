#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc , char * argv[]) {
    int fd;
    
    if(argc != 2) {
        printf("You have to run this program with exactly one argument!\n");
        return 1;
    }
    if((fd = open(argv[1] , O_RDWR|O_CREAT , S_IRUSR|S_IWUSR) == -1)) {
        printf("Can't open %s!\n" , argv[1]);
        return 2;
    }
    printf("Opened %s with read-write et create rights!\n" , argv[1]);
    
    int nb_wr = write(fd , "abcdefg" , 7);
    printf("Wrote %d characters to %s!\n" , nb_wr , argv[1]);
    printf("You can check rights with ls -l, return afterwards\n");
    getchar();
    
    int retchmod = chmod("new.file" , S_IRUSR|S_IRGRP);
    if(retchmod != 0) {
        printf("Error while calling chmod()!\n");
        return 3;
    }
    printf("chmod() is a success!");
    nb_wr = write(fd , "hijklmn" , 7);
    printf("Wrote %d characters to %s!\n" , nb_wr , argv[1]);
    printf("Waiting for return\n");
    getchar();
    close(fd);
    printf("File closed\n");
    printf("Waiting for return, we'll edit rights again after\n");
    retchmod = chmod("new.file" , S_IRWXU);
    if(retchmod != 0) {
        printf("Error while calling chmod()!\n");
        return 4;
    }
    return 0;
}