
#ifndef FicTP3_H
#define FicTP3_H


bool estTrieeLSC(ListeSC L);
  //   Res : Renvoie true si L est une ListeSC triée, false sinon 

bool estListeIntervalle(ListeSC L);
  //   Res : renvoie true si L est une Liste intervalle, renvoie false sinon 

ListeSC consListeIntervalle1(int l, int p);
  //     Donnée : l>0 
  //     Res : renvoie une liste intervalle de longueur l et dont le premier élément a pour valeur p 

ListeSC consListeIntervalle2(int l, int p);
  //     Donnée : l>0 
  //     Res : renvoie une liste intervalle de longueur l et dont le premier élément a pour valeur p 

ListeSC consListeIntervalle3(int l, int p);
  //     Donnée : l>0 
  //     Res : renvoie une liste intervalle de longueur l et dont le premier élément a pour valeur p 


void transfListeIntervalle(ListeSC L);
  // Donnée : L est une liste triée non vide  
  // Res : modifie L en y inserant des éléments de sorte qu'elle soit une Liste Intervalle 

ListeSC intersectionListesIntervalles(ListeSC l1, ListeSC l2);
  // Donnée : l1 et l2 2 listes intervalles
  // Res : Renvoie l'intersection de l1 et l2; les éléments de la liste résultat sont recopiés

 
void plusLgSsLiInterv(ListeSC &L);
  // Donnée : L liste
  // Res : L est modifiee, elle est la lus longue sous-liste intervalle de la liste en entrée


#endif 




