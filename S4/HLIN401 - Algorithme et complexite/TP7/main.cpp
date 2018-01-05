#include <iostream>
#include "ArbreBinaireRecherche.h"

////// Odorico Thibault //////

using namespace std;

int main(int argc, char** argv) {

  ABR A1 = new SommetABR(11);

  A1->InsererValeur(5);
  A1->InsererValeur(15);
  A1->InsererValeur(3);
  A1->InsererValeur(9);
  A1->InsererValeur(7);
  A1->InsererValeur(8);
  A1->InsererValeur(10);

  SortieLatex(A1, "Dessin Arbre A1");
  
  ABR A2 = new SommetABR(11);
  
  A2->InsererValeur(5);
  A2->InsererValeur(15);
  A2->InsererValeur(3);
  A2->InsererValeur(9);
  A2->InsererValeur(7);
  A2->InsererValeur(8);
  A2->InsererValeur(10);
  
  A2->SupprimerValeur(5);
  
  SortieLatex(A2, "Dessin Arbre A2");
  
  cout << "A1->inclusN(A2)? " << A1->inclusN(A2) << endl;
  cout << "A2->inclusN(A1)? " << A2->inclusN(A1) << endl;
 
  return 1;
}

/* compiler avec g++ main.cpp ArbreBinaireRecherche.cpp SortieLatex.cpp  */
