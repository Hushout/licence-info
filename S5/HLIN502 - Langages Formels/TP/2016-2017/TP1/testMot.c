#include <stdio.h>
#include "mot.h"

int main(int n, char *argv[], char *env[]){
  mot m1=motCreer();
  mot m2="";
  if (!motEstVide(motConcatMot(m1,m2)))
    printf("Probleme motConcatMot !");
  m1=symboleConcatMot('a',"bc");
  m2=motConcatSymbole("ab",'c');
  if (!motEgalMot(m1,m2))
    printf("Probleme motEgalMot ! m1 : %s; m2 : %s\n",m1,m2);
  printf("mot %s decompose en tete : %c, et queue : %s \n",m1,motTete(m1),motQueue(m1));
  printf("miroir de : Esope reste i.c.i et se repose : %s\n", motMiroir(motConcatMot(motConcatSymbole("Esope reste i",'c'),"i et se repose")));
  
  langage l=langageAjouterMot(langageAjouterMot(langageCreer(),"premierMotAjoute"),"deuxieme");
  langageAfficher(l);
  langage l2=langageAjouterMot(langageAjouterMot(langageAjouterMot(langageCreer(),m1),"premierMotAjoute"),"deuxieme");
  langageAfficher(langageUnionLangage(l,l2));
//  langageAfficher(motPrefixes("abcde"));
}
