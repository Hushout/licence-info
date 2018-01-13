#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //fork(), getpid(),
#include <sys/types.h> //renvoie des types pid_t
#include <sys/wait.h>

//le dernier processus vivant sera le premier lancé.
int main(int argc, char** argv){

  int nbEspace = 0;
  for(int i=0 ; i<4 ; i++){
     
    pid_t nPid;

    if ((nPid = fork()) == 0){
      for(int j = 0; j < nbEspace ; j++){
        printf(" ");
      }
      printf("un nouveau descendant %d de parent %d ! i=%d\n", getpid(), getppid(),i);
      nbEspace +=4;
    }
    else{
      int status;
      wait(&status);
    }//chaque parent attend la fin de ses enfants
  }
return 0;
}
