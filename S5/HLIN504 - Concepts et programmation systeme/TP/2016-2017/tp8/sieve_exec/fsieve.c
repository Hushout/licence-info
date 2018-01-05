#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc , char * argv[]) {
    pid_t child;
    int prime;
    int out[2];
    
    if(read(0 , (void *)&prime , sizeof(int)) != sizeof(int)) {
        return 0;
    }
    
    printf("%d\n" , prime);
    if(-1 == pipe(out)) {
        printf("Error while creating pipe\n");
        exit(1);
    }
    
    switch(child = fork()) {
        case -1 :
            printf("There was an error while forking\n");
            exit(2);
            break;
        case 0 :
            close(out[1]);
            dup2(out[0] , 0);
            close(out[0]);
            execl("fsieve" , "fsieve" , NULL);
            break;
        default :
            close(out[0]);
            int i;
            while(read(0 , (void *)&i , sizeof(int)) == sizeof(int))
                if(i % prime)
                    write(out[1] , (void *)&i , sizeof(int));
            close(out[1]);
            wait(0);
            break;
    }
}