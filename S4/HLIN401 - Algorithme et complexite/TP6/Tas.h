#ifndef TAS_H
#define TAS_H

#include <iostream>
#include <sstream>

#include "AB.h"

//h = log (n)
//n = 2^h
//filsG indiceSommet i = 2i + 1
//filsD indiceSommet i = 2i + 2
//remonter descendre supprimerRacine ajouter

typedef int indiceSommet;

class ArbreParfait
{
 public:
  int IndicePremierSommetLibre;
  int NombreMaximalDeSommets;
  int* contenu;
  void Echanger(indiceSommet,indiceSommet);

 public:
  ArbreParfait(int);
  // on passe la nombre max de sommet de l'arbre, la hauteur de cette arbre = log(n);


  int AjouteSommetArbreParfait(Valeur);
  // renvoie -1 si l'ajout a échoué

  void SupprimerDansArbreParfait(indiceSommet);

  bool SommetValide(indiceSommet);

  int Racine();
  bool FeuilleP(indiceSommet);
  indiceSommet Pere(indiceSommet);
  indiceSommet FilsGauche(indiceSommet);
  indiceSommet FilsDroit(indiceSommet);

  void SupprimerArbreParfait(indiceSommet);
};


class Tas : public ArbreParfait {
 public:
  Tas(int);

  void Remonter(indiceSommet);
  void Descendre(indiceSommet);

  void SupprimerTas(indiceSommet);

  void AjouterTas(Valeur);

  int Supmin();

  void DescendreRecursive(indiceSommet i, AB A);

  AB TasVersABRec(indiceSommet);
  AB TasVersAB();

};

bool estPair(int);

#endif
