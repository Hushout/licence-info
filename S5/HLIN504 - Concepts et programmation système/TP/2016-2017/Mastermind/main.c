#include "mm.h"
#include <stdio.h>
#include <unistd.h>

int main(){
  mm j=mm_creer();
  //printf("%s\n",j->secret);
  char saisie[1024];
  int res;
  do{
    printf("?");
    scanf("%s",saisie);
    res=mm_test(j,saisie);
    if (res==-1)
      printf("Erreur de saisie !\n");
    else if (res==0)
      printf("Aucune lettre correcte !\n");
    else {
      printf("%d lettres bien placees, %d lettres mal placees !\n", res/(TAILLE+1),res%(TAILLE+1));
      if(res/(TAILLE+1)==TAILLE){
	printf("BRAVO ! Vous avez reussi en %d  essais !\n",mm_nbessais(j));
	//sleep(2);
      }
    }
  }while(res!=TAILLE*(TAILLE+1));
}
