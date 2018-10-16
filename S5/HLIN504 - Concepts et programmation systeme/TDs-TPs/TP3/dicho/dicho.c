#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char * argv[]) {
    int input,
    begin = 0,
    middle,
    end,
    i;
    char c , x;
    
    if(argc != 3) {
        printf("You need to run this program with exactly one argument!\n");
        return 1;
    }
    input = open(argv[1] , O_RDONLY);
    if(input < 0) {
        printf("Can't open %s\n" , argv[1]);
        return 2;
    }
    x = argv[2][0];
    end = lseek(input , 0 , SEEK_END) - 1;
    if(end == -2) {
        printf("Can't parse file\n");
        return 3;
    } else if (end == -1) {
        printf("File is empty\n");
        return 4;
    }
    
    do {
        middle = (begin + end) / 2;
        i = lseek(input , middle , SEEK_SET);
        if(i == -1) {
            printf("Can't go to %d in %s\n" , middle , argv[1]);
            return 5;
        }
        i = read(input , &c , 1);
        if(i != 1) {
            printf("Can't read in %s\n", argv[1]);
            return 6;
        }
        if(c > x)
            end = middle - 1;
        else if(c < x)
            begin = middle + 1;
    } while(c != x && begin <= end);
 
    if(c == x)
        printf("%c is at %d in %s\n" , c , middle , argv[1]);
    else
        printf("Can't find %c in %s\n" , x , argv[1]);

    close(input);
    return 0;
}