#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc , char * argv[]) {
    printf("Hello, world!\n");
    char * s = malloc(strlen(argv[0]) + 3);
    strcat(strcpy(s , argv[0]) , ".c");
    int exe = execlp("gcc" , "gcc" , "-o" , argv[0] , s , NULL);
    if(exe == -1)
        printf("There was an error\n");
    else
        printf("Impossibe!\n");
    return 0;
}