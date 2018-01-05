#include "score.h"

Score::Score() : _point(0){}

int Score::calcul(const int multiplicateur){
  
  if( multiplicateur == 0){
    return 0;}
  if( multiplicateur == 1){
    return 10;}
  if( multiplicateur == 2){
    return 25;}
  if( multiplicateur == 3){
    return 45;}
  if( multiplicateur == 4){
    return 60;}
  if( multiplicateur == 5){
    return 75;}
  if( multiplicateur == 6){
    return 90;}
  return 0;
}

bool Score::verifLigne(const Matrice& M, int i){
  bool test = true;
  size_t j = 0;
  while(j < M.getLargeur() && test==true){
    if (M.at(i,j)== 0){
      test=false;
    }
    j++;
  }
  return test;
}

bool Score::verifColonne(const Matrice& M, int j){
  bool test=true;
  size_t i=0;
  while( i<M.getHauteur() && test==true){
    if (M.at(i,j)==0){
      test=false;
    }
    i++;
  }
  return test;
}

void Score::Actualisation( Matrice& M){
  
  bool tabDestructionLigne[10];
  bool tabDestructionColonne[10];
  falseTab( tabDestructionLigne, 10);
  falseTab( tabDestructionColonne, 10);
  size_t i=0;
  size_t j=0;
  int dest1=0;
  int multiplicateurL=0;
  int multiplicateurC=0;
  while (i<M.getHauteur()){
    if(verifLigne( M, i)==true){
      tabDestructionLigne[i]=true;
      multiplicateurL++;
    }
    i++;
  }
  while (j<M.getLargeur()){
    if( verifColonne(  M, j)==true){
      tabDestructionColonne[j]=true;
      multiplicateurC++;
    }
    j++;
  }
  if (multiplicateurC>0 && multiplicateurL>0){
    _point= _point + 2 * (calcul(multiplicateurC) + calcul(multiplicateurL));
  }
  else {
    _point= _point  + calcul(multiplicateurC) + calcul(multiplicateurL);
  }
  
  while( dest1<10){
    if(tabDestructionLigne[dest1]==true){
      M.setLigne(dest1, 0);
    }
    dest1++;
  }
  dest1=0;
  while (dest1<10){
    if( tabDestructionColonne[dest1]==true){
      M.setColonne(dest1, 0);
    }
    dest1++;
  }
}

void falseTab(bool* tableau, int taille){
  int i=0;
  while(i < taille){
    tableau[i]=false;
    i++;
  }
}


//ANTOINE&TRISTAN(ps: n'oublie le putain de makefile cordialement thibault)

