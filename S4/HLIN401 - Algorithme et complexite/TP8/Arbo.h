#ifndef ARBO_H
#define ARBO_H

#include <iostream>
#include <sstream>

using namespace std;

typedef int Valeur;

struct Sommet;
typedef Sommet* Arbo;

/******* Liste chainee Début *******/
struct Cellule;

typedef Cellule* ListeCellules;

struct Cellule{
  Arbo fils;
  ListeCellules Apres;

  Cellule (Arbo A);

  ListeCellules EstDansListeP(Arbo A); 
// Si A apparait dans la liste, renvoie un pointeur sur la sous liste commençant par A; sinon renvoie NULL 

  ListeCellules AjouterSuccesseur(Arbo A);
// si A appartenait déjà à la liste renvoie la liste
// sinon rajoute A en tete et renvoie le nouvelle liste


  ListeCellules RetirerSuccesseur(Arbo A);
// renvoie la liste d'où a été retirée A s'il lui appartenait (sinon renvoie la liste initiale)
};

/******* Liste  chainee Fin *******/

/************Arborescence Debut*************/
struct Sommet {
  Valeur racine;
  ListeCellules ListeSuccesseurs;
 

  Sommet(Valeur v);

  ListeCellules EstSuccesseurP(Arbo A);
// Si A apparait dans la liste ListeSuccesseurs, renvoie un pointeur sur la sous liste  de ListeSuccesseurs commençant par A; sinon renvoie NULL

  void AjouterSuccesseur(Arbo A);
//rajoute A comme fils ainé

  void RetirerSuccesseur(Arbo A);
// si A était un fils, il cesse de l'être
};

ostream& operator<<(ostream& os, Sommet& S);

/************Arborescence  Fin*************/

/************Traversee recursive Debut*************/

void TraverseePrefixeRec(Arbo);

/************Traversee recursive Fin*************/

/**********Pile Début*********/
struct Pile {
  ListeCellules Sommet;

  Pile();

  bool VideP();
  void Empiler(Arbo);
  Arbo Depiler(); // pas défini si la pile est vide
};

/**********Pile Fin*********/

/************Traversee prefixe iterative Debut*************/

void TraverseePrefixeIt(Arbo);

/************Traversee  prefixe iterative Fin*************/

/**********File Début*********/
struct File {
  ListeCellules Sortie;
  ListeCellules Entree;

  File();

  bool VideP();
  void Enfiler(Arbo);
  Arbo Defiler(); // pas défini si la pile est vide
};

/**********File Fin*********/

/************Traversee Largeur Debut*************/

void TraverseeLargeur(Arbo);

/************Traversee Largeur Fin*************/

#endif
