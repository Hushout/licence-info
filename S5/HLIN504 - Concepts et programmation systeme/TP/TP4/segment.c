#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //fork(), getpid(),
#include <sys/types.h> //renvoie des types pid_t
#include <sys/wait.h>
#include <string.h>

//le dernier processus vivant sera le premier lancé.
int main(int argc, char** argv){

  int nbEspace = 4;
  printf("Main pid: %d, ppid %d\n", getpid(), getppid());

  FILE* f = fopen("text.txt", "w+");

  if(!f){
    printf("Erreur ouverture fichier impossible");
  }
  else{
    int n = 2;

    for(int i=0;i<n;i++) // loop will run n times (n=5)
    {
        if(fork() == 0)
        {
          int a = 1, b = 2, c = 3;
          printf("Fils pid: %d, ppid %d, adr a: %p, adr b: %p, adr c: %p\n", getpid(), getppid(), &a, &b, &c);
          char string[1000] = {0};
          char spid[1000] = {0};
          sprintf(spid, "%d", getpid());
          strcat(string, spid);
          strcat(string, " ecrit\n");
          fputs(string, f);
          exit(0);
        }
    }
    for(int i=0;i<n;i++){
      wait(NULL);
    }

    fclose(f);
  }
  return 0;
}
