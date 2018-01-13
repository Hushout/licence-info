#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char * argv[]) {
    int nb_char = 0;
    int chars[256];
    char c;

    if(argc != 2) {
        printf("You need to run this program with exactly one argument!\n");
        return 1;
    }
    int input = open(argv[1] , O_RDONLY);
    if(input < 0) {
        printf("Can't open %s\n" , argv[1]);
        return 2;
    }
    for(int i = 0 ; i < 256 ; i++)
        chars[i] = 0;
    while(0 < read(input , &c , 1)) {
        if(!chars[(int)c]) {
            chars[(int)c] = 1;
            nb_char++;
        }
    }
    close(input);
    printf("There are %d different characters" , nb_char);
    for(int i = 0 ; i < 256 ; i++)
        if(chars[i])
            printf("%c" , i);
    printf("\n");
    return 0;
}