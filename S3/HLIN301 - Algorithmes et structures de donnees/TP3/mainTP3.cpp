#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "progListeSC.h"
#include "fichierTP3.h"

using namespace std;


int main(int argc, char *argv[]){
  ListeSC l1,l2,l3;
  int q, lg, prem;
  clock_t t1,t2,t3, t4;

  cout << "Numero de la question traitee (1/2/3/4/5/6) ? ";
  cin >> q ;
    switch (q){
    case 1 :
      l1=lireLSC();
      if (estListeIntervalle(l1))
	cout << "Cette liste est une liste intervalle \n";
      else
	cout << "Cette liste n'est pas une liste intervalle \n";
      break;
      
    case 2 :
      cout << "Donnez 2 entiers strictement positifs (longueur et premier element de la liste intervalle) : ";
      cin >> lg >> prem;
      l1=consListeIntervalle1(lg,prem);
      afficherLSC(l1);
      l2=consListeIntervalle2(lg,prem);
      afficherLSC(l2);
      l3=consListeIntervalle3(lg,prem);
      afficherLSC(l3);
      break;
    case 3 :
      cout << "Donnez 2 entiers strictement positifs (longueur et premier element de la liste intervalle) : ";
      cin >> lg >> prem;
      t1=clock();
      l1=consListeIntervalle1(lg,prem);
      t2=clock();
      l2=consListeIntervalle2(lg,prem);
      t3=clock();
      l3=consListeIntervalle3(lg,prem);
      t4=clock();
      
      cout << " Construction d'une Liste de taille " <<   lg 
	   << "\n  version 1 "  <<(double) (t2-t1)/CLOCKS_PER_SEC 
	   << " sec\n  version 2 " <<(double) (t3-t2)/CLOCKS_PER_SEC 
	   << " sec\n version 3 "<<(double) (t4-t3)/CLOCKS_PER_SEC<< " sec\n";
      break;
    case 4 : // Transformation d'une liste triee en liste Intervalle 
      cout << "Entrez une Liste Triee : ";
      l1=lireLSC();
      transfListeIntervalle(l1);
      cout << "Liste Intervalle construite ";
      afficherLSC(l1);
      break;
    case 5 : // intersection de 2 listes intervalle
      cout << "Liste intervalle : ";
      l1=lireLSC();
      cout << "Liste intervalle : ";
      l2=lireLSC();
      l3=intersectionListesIntervalles(l1,l2);
      cout << "Intersection : \n";
      afficherLSC(l3);
      break;
    case 6 :
      cout << "Entrez une Liste  : ";
      l1=lireLSC();
      plusLgSsLiInterv(l1);
      cout << "Plus longue sousListe Intervalle : ";
      afficherLSC(l1);
     }
    return 0;
}





