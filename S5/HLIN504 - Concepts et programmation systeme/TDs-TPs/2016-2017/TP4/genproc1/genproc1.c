#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    switch(pid = fork()) {
    case -1 :   //ERROR
        printf("Error while forking\n");
        break;
        
    case 0 :    //PARENT PROCESS
        printf("Descendant : fork() return value: %d\n" , pid);
        printf("Descendant : I am %d, my parent is %d\n" , getpid() , getppid());
        return 4;
        break;
        
    default :   //CHILD PROCESS
        printf("Parent : fork() return value: %d\n" , pid);
        printf("Parent : I am %d, my parent is %d\n" , getpid() , getppid());
        int status = 0;
        pid_t child = waitpid(pid , &status , 0);
        printf("Parent : death of %d with status %d\n" , child , WEXITSTATUS(status));
        break;
    }
    return 0;
}