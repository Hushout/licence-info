//SortieLatex.cpp

#include <iostream>
#include <cstdlib>
#include "Tas.h"

// Compte le nombre de tour du processeur
unsigned long long rdtsc(){
  unsigned int lo, hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return ((unsigned long long) hi << 32) | lo;
}

// Graine pour initialiser la fonction aleatoire
int randomSeed(){return rdtsc();}

// Genere une nombre aleatoire sur l'intervalle [min, max[
int randInter(int min, int max){
  
  //initialise la fonction aleatoire
  srand(randomSeed());
  
  return rand() % (max - min) + min;
}


void afficheTas(Tas T){

  for(int i = 0 ; i < T.IndicePremierSommetLibre; i++){
    std::cout << "Tas[" << i << "] = " << T.contenu[i] << std::endl;
  }
}

int main(int argc, char** argv){

  if(argc == 2){
    
    int min = 0;
    int max = 100;
    int taille = atoi(argv[1]);

    //Creer un Tas d'une taille variable avec des valeurs aléatoires entre min et max
    Tas T(taille);

    for(int i = 0 ; i < taille ; i++){
      T.AjouterTas(randInter(min, max));
    }

    if(taille >= 10){
      //Supprime 3 sommet Aleatoirement dans le tas
      T.SupprimerTas(randInter(0, T.IndicePremierSommetLibre-2));
      T.SupprimerTas(randInter(0, T.IndicePremierSommetLibre-2));
      T.SupprimerTas(randInter(0, T.IndicePremierSommetLibre-2));
    }

    //Convertie le Tas en Arbre binaire
    AB A = T.TasVersAB();

    //Dessine L'arbre dans un pdf
    SortieLatex(A, "MonTas");
  }
  else{
    std::cout << "[Guide d'utillisation]"<< std::endl << std::endl;
    std::cout << "[Comment executer ?]"<< std::endl;
    std::cout << "-> " << argv[0] << " <taille>" << std::endl << std::endl;
    std::cout << "[Qu'est ce que ça fait ?]" << std::endl;
    std::cout << "-> Ce programme Creer un Tas qui sera de la taille rentrée en parametre, il l'inialise avec des valeur prisent au hasard, Si la taille du tas est plus grande que 9, 3 Sommets du tas seront supprimer au hasard, dans tout les cas le tas sera convertis en Arbre binaire et dessiné dans un pdf." << std::endl;
  }
  return 0;
}
