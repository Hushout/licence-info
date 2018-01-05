#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "progListeSC.h"
#include "fichierTP3.h"
using namespace std;



bool estTrieeLSC(ListeSC L){
  //   Res : Renvoie true si L est une ListeSC triée, false sinon 

  if (estVideLSC(L) || estVideLSC(L->succ))
    return true;
  else
    return (L->info < (L->succ)->info) &&  estTrieeLSC(L->succ);
}



bool estListeIntervalle(ListeSC L){
  //   Res : renvoie true si L est une Liste intervalle, renvoie false sinon 
  // A COMPLETER
  ListeSC P = L;
  if(L->succ == NULL){
      return true;
  }
  while(P->succ != NULL){
    if(P->info+1 != (P->succ)->info){
      return false;
    }
    P = P->succ;
  }
  return true;
}

ListeSC consListeIntervalle1(int l, int p){
  //     Donnée : l>0 
  //     Res : renvoie une liste intervalle de longueur l et dont le premier élément a pour valeur p 
  //     Complexité : l^2
  assert(l>0);
  
  int i; ListeSC L;
  L=NULL;
  for(i=0;i<l;i++)    
    insererFinLSC(L,p+i);
  return L;
}

ListeSC consListeIntervalle2(int l, int p){
  //     Donnée : l>0 
  //     Res : renvoie une liste intervalle de longueur l et dont le premier élément a pour valeur p 
  //     Complexité : l  
  assert(l>0);
  // A COMPLETER
  int i; ListeSC L;
  L=NULL; int k = l;
  for(i=0;i<l;i++){
    L = creerLSC(p+k-1, L);
    k--;
  }
  return L;
}


ListeSC consListeIntervalle3(int l, int p){
  //     Donnée : l>0 
  //     Res : renvoie une liste intervalle de longueur l et dont le premier élément a pour valeur p 
  //     Complexité : l 
  // Version récursive
  assert(l>0);
  // A COMPLETER
  if(l < 2){
    return creerLSC(p, NULL);
  }
  else{
    return creerLSC(p, consListeIntervalle3(l-1, p+1));
  }
}

void transfListeIntervalle(ListeSC L){
  // Donnée : L est une liste triée non vide  
  // Res : modifie L en y inserant des éléments de sorte qu'elle soit une Liste Intervalle 
  assert((L!=NULL));
  assert(estTrieeLSC(L));
  // A COMPLETER
  ListeSC P = L;
  if(estListeIntervalle(L)){
    exit(0);
  }
  while(P->succ != NULL){
    if(!(P->info+1 == (P->succ)->info)){
      insererApresLSC(L, P, P->info+1);
    }
    P = P->succ;
  }
}

ListeSC intersectionListesIntervalles(ListeSC l1, ListeSC l2){
  // Donnée : l1 et l2 2 listes intervalles
  // Res : Renvoie l'intersection de l1 et l2; les éléments de la liste résultat sont recopiés
  // Complexité : ????
  // A COMPLETER
  assert(estListeIntervalle(l1));
  assert(estListeIntervalle(l2));
  ListeSC P1, P2, R;
  if(l1->info <= l2->info){
    P1 = l1; P2 = l2; 
  }
  else{
    P1 = l2; P2 = l1; 
  }
  while(P1 != NULL){
    if(P1->info == P2->info){
      insererFinLSC(R, P1->info);
      P2 = P2->succ;
    }
    P1 = P1->succ;
  }
  return R  ;
}
  
void plusLgSsLiInterv(ListeSC &L){
  // Donnée : L liste
  // Res : L est modifiee, elle est la lus longue sous-liste intervalle de la liste en entrée
  // A COMPLETER

}





