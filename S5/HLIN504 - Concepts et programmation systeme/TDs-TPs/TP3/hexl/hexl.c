#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char * argv[]) {
    int position = 0, nb, c[16];
    
    if(argc != 2) {
        printf("You need to run this program with exactly one argument!\n");
        return 1;
    }
    int input = open(argv[1] , O_RDONLY);
    if(input < 0) {
        printf("Can't open %s\n" , argv[1]);
        return 2;
    }
    while(0 < (nb = read(input , &c , 16))) {
        printf("%8.8x : ", position);
        position += 16;
        for(int i = 0 ; i < nb ; i++) {
            char code = c[i];
            printf("%2.2hhx" , code);
            if(i % 2)
                printf(" ");
        }
        if(nb < 16) {
            for(int i = nb ; i < 16 ; i++) {
                printf("  ");
                if(i % 2)
                    printf(" ");
            }
        }
        printf(" ");
        for(int i = 0 ; i < nb ; i++) {
            if(c[i] >= 0x20 && c[i] < 0x7F)
                printf("%c" , c[i]);
            else
                printf(".");
        }
        printf("\n");
    }
    close(input);
    return 0;
}