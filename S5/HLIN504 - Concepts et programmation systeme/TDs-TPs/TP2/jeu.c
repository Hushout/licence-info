// jeu : le but du jeu est de deviner un nombre entre 0 et 9

#include <stdio.h>
#include <stdlib.h>		//pour random
#include <unistd.h>		/* pour crypt */
#include <string.h>

#include "es.h"
#include "alea.h"

int main(){
  printf("JEU : DEVINEZ UN NOMBRE ENTRE 1 ET 9\n");
  initalea();
  int nb_a_deviner=(int)random()%9;
  int nb_devine=entnb();
  if (nb_devine == nb_a_deviner) {
    printf("Bravo !!\n");
  }
  else {
    printf("Erreur, l'entier a deviner etait :");
    sortienb(nb_a_deviner);
  }
  char mot[256];
  printf("Saisie du mot de passe : ");
  scanf("%s",mot);
  printf("\nmot saisi : %s \n",  mot);
  printf("mot crypte : ");
  printf(crypt(mot, "az"));
  printf(" \n");
}
