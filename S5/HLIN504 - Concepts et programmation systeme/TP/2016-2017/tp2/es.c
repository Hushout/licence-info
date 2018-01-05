// gestion des E/S standard pour l'application jeu
// implementation
//

#include <stdio.h>
#include "es.h"


// lecture d'un nombre entier depuis le fichier d'entree std
int entnb(){
  int nb;
  printf("Entrez un nombre : ");
  scanf("%d",&nb);
  return nb;
}
// ecriture d'un entier dans le fichier de sortie std
void sortienb(int i){
  printf("entier : %d\n", i);
}
