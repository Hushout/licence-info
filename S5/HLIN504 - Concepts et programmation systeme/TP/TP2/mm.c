#include "mm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

mm mm_creer(){
  mm newMm = malloc(sizeof(mm));
  newMm->nbessais = 0;
  srand(time(NULL));
  for(int i = 0 ; i < TAILLE ; i++){
    newMm->secret[i] = rand() % 10;
  }
  newMm->secret[TAILLE] = '\0';
  printf("%s", newMm->secret);
  
  return newMm;
}
/**
 * Supprime un jeu en désallouant la mémoire
 * @param mm un pointeur sur la structure de jeu
 */
void mm_detruire(mm jeu){
  free(jeu);
}
/**
 * teste un mot essai face au mot secret stocké dans le jeu
 * @param jeu un pointeur sur la structure de jeu
 * @param essai la chaîne de caractères proposée par le joueur humain
 * @returns un entier contenant (TAILLE+1)*nb lettres bien placées + nb lettres
 * mal placées; -1 si l'essai est erroné (nb lettres, ...)
 */

int mm_test(mm jeu, char* essai){
  char c = -1;
  int taille = 0;
  while(c != '\0'){
    c = essai[taille];
    taille++;
  }

  if(taille-1 != TAILLE)
    return -1;
    
    int bienPosey = 0;
    int malPosey = 0;
    char* secret = jeu->secret;
    
    for(int i = 0; i < TAILLE; i++){
      for(int j = 0; j < TAILLE; j++){
      
	if(secret[i] == essai[j]){
	
	  if( i == j)
	    bienPosey ++;
	  else
	    malPosey ++;
	}
      }
    }
  
    return ( TAILLE + 1 ) * bienPosey + malPosey; 
  }

/** Retourne le nb d'essais déjà effectués 
 * @param jeu un pointeur sur la structure de jeu
 * @returns le nombre d'essais
 */
int mm_nbessais(mm jeu){
  return jeu->nbessais;
}
