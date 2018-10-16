/*
 * implemente une fonction C initialisant le generateur de nombre aleatoire
 * en fonction de l'heure systeme.
 */
#include<time.h>
#include<stdlib.h>
#include"alea.h"

void initalea(){
  time_t tps;
  tps=time(0);  /* lecture de l'heure systeme
		   nombre de secondes depuis le 01.01.70 */
  srandom((unsigned)tps); /* initialisation */
}
