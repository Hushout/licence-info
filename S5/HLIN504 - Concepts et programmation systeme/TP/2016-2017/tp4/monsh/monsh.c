#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc , char * argv[]) {
    char command[1000];
    do {
        printf("$");
        scanf("%s" , command);
        if(!strcmp(command , "exit"))
            return 0;
        
        pid_t pid = fork();
        switch(pid) {
            case -1 :
                printf("Error while forking\n");
                return 1;
                break;
                
            case 0 :
                execlp(command , command , NULL);
                break;
            
            default :
                wait(NULL);
                break;
        }
    } while(1);
    
    return 0;
}