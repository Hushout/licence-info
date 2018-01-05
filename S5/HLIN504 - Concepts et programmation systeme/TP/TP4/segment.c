#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //fork(), getpid(),
#include <sys/types.h> //renvoie des types pid_t
#include <sys/wait.h>

//le dernier processus vivant sera le premier lancé.
int main(int argc, char** argv){
  
  int nbEspace = 4;
  int nPid;
  int a = 1, b = 2, c = 3;

  printf("Main pid: %d, adr a: %p, adr b: %p, adr c: %p\n", getpid(), &a, &b, &c);

  if((nPid = fork()) == 0){
    printf("Fils pid: %d, ppid %d, adr a: %p, adr b: %p, adr c: %p\n", getpid(), getppid(), &a, &b, &c);
  }
  else{
    int status;
    wait(&status);
  }

  return 0;
}
