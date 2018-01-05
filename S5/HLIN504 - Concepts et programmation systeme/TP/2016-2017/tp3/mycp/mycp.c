#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char * argv[]) {
    int input,
        output;
    char c;
    
    if(argc != 3) {
        printf("You need to run this program with exactly one argument!\n");
        return 1;
    }
    input = open(argv[1] , O_RDONLY);
    if(input < 0) {
        printf("Can't open %s\n" , argv[1]);
        return 2;
    }
    output = open(argv[2] , O_WRONLY|O_CREAT|O_TRUNC , 0x644);
    if(output < 0) {
        printf("Can't open %s\n" , argv[2]);
        return 3;
    }
    while(0 < (read(input , &c , 1))) {
        write(output , &c , 1);
    }
    close(input);
    close(output);
    return 0;
}