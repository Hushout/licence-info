#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    for(int i = 0 ; i < 4 ; i++) {
        pid_t nPid;
        if((nPid = fork()) == 0) {
            printf("A new child process %d spawned from %d\n" , getpid() , getppid());
        } else {
            pid_t status;
            wait(&status);
        }
    }
    return 0;
}