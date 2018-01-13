#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Hello, world!\n");
    int exe = execl("/bin/ls" , "ls" , "-l" , "/bin/" , NULL);
    if(exe == -1)
        printf("There was an error\n");
    else
        printf("Impossibe!\n");
    return 0;
}