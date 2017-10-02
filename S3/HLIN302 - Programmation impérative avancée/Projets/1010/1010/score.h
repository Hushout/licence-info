#ifndef SCORE_H
#define SCORE_H

#include "matrice.h"

class Score{

 private:

  int _point;

 public:

  Score();

  int getPoint(){return _point;}
  void setPoint(int point){_point = point;}

  // Calcul les points à ajouter grâce au multiplicateur
  int calcul(const int _multiplicateur);
  
  //Vérifie si la ligne i est full
  bool verifLigne(const Matrice& M, int i);
  
  //Vérifie si la ligne j est full
  bool verifColonne(const Matrice& M, int j);
  
  // Verifie la matrice, la modifie et actualise le score grâce au multiplicateur
  void Actualisation(Matrice& M);
};

//Remet à false chaque case du tableau
void falseTab(bool* tableau, int taille);

#endif


// ANTOINE
