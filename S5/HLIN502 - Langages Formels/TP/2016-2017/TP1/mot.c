#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mot.h"

/** toutes les fonctions de base sur mot commencent par motMajuscule...
 */
/** retourne un mot vide */
mot motCreer(){
  return "";
}
/** concatène un symbole et un mot pour former un nouveau mot
 * retourne le mot c.m
 * ne modifie pas le mot m
 */
mot symboleConcatMot(symbole c, mot m){
  mot nouv=(mot)malloc(2+strlen(m)); // 1 pour c, 1 pour \0
  nouv[0]=c;
  strcpy(nouv+1,m);
  return nouv;
}
mot motConcatSymbole(mot m, symbole c){
  mot nouv=(mot)malloc(2+strlen(m)); // 1 pour c, 1 pour \0
  strcpy(nouv,m);
  nouv[strlen(m)]=c;
  nouv[strlen(m)+1]='\0';
  return nouv;
}
mot motCopier(mot m){
  return strdup(m);
}
/** retourne vrai ssi m est vide
 */
int motEstVide(mot m){
  return strlen(m) == 0;
}
/** retourne ce mot sans sa première lettre
 * prérequis : ce mot n'est pas vide
 */
mot motQueue(mot m){
  return m+1;
}
/** retourne la première lettre de ce mot
 * prérequis : ce mot n'est pas vide
 */
symbole motTete(mot m){ 
  return m[0]; 
}
mot motConcatMot(mot un, mot deux){
  if (motEstVide(un))
    return deux;
  else if (motEstVide(deux))
    return un;
  else
    return symboleConcatMot(motTete(un),motConcatMot(motQueue(un),deux));
}
mot motMiroir(mot m){
  if (motEstVide(m)||motEstVide(motQueue(m)))
    return m;
  else
    return motConcatSymbole(motMiroir(motQueue(m)),motTete(m));
}
int motEgalMot(mot un, mot deux){
  return !strcmp(un,deux);
}

/** langage : ensemble (liste chaînée sans doublons) de mots. un langage n'est 
 * pas mutable : on ne peut le modifier.
 */

/** crèe un langage vide : une liste vide.
 */
langage langageCreer(){
  return NULL;
}
int langageEstVide(langage l){
  return l==NULL;
}
/** teste l'appartenance d'un mot à un langage
 */
int langageContientMot(langage l, mot m){
  if (langageEstVide(l)) 
    return 0;
  else if (motEgalMot(m, langagePremierMot(l))) 
    return 1;
  else 
    return langageContientMot(langageReste(l),m);
}
/** retourne un nouveau langage contenant m et l
 */
langage langageAjouterMot(langage l, mot m){
  if (!langageContientMot(l,m)){
    langage nouv=(langage)malloc(sizeof(struct cellule));
    nouv->m=m;
    nouv->suiv=l;
    return nouv;
  } else {
    return l;
  }
}
/** retourne le premier mot du langage
 * prérequis : l est non vide
 */
mot langagePremierMot(langage l){
  return l->m;
}
/** retourne le langage privé de son premier mot
 * prérequis : l est non vide
 */
langage langageReste(langage l){
  return l->suiv;
}
void langageAfficher(langage l){
  if (!langageEstVide(l)) {
    printf("<%s> ",langagePremierMot(l)); 
    langageAfficher(langageReste(l));
  } else {
    printf("\n");
  }
}
langage langageUnionLangage(langage l1, langage l2){
  if (langageEstVide(l1))
    return l2;
  else if (langageEstVide(l2))
    return l1;
  else
    return langageAjouterMot(langageUnionLangage(langageReste(l1),l2),langagePremierMot(l1));
} 
