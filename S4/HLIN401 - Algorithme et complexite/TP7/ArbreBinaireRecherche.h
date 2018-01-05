#ifndef ARBREBINAIRERECHERCHE_H
#define ARBREBINAIRERECHERCHE_H

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

class SommetABR;

typedef SommetABR *ABR;

typedef int Valeur;

class SommetABR{

 public:
  Valeur racine;
  ABR Pere, SAG, SAD;
  bool FGP;
  
 public:
  SommetABR(Valeur v);
  SommetABR(SommetABR& s);

  void GrefferSAG(ABR g);
  void GrefferSAD(ABR d);

  void SupprimerSAG();
  void SupprimerSAD();

  bool FeuilleP();

  void RemplacerPourLePerePar(ABR);

  friend std::string* TikzRecursABR(int ligne,int gauche, int droite, int numeroPere, int typeFils, ABR Ar);

// ABR

  ABR PlusPetit();
  ABR RechercherValeur(Valeur v);
  void InsererValeur(Valeur v);
  ABR SupprimerValeur(Valeur v); // notez la dissymétrie
  ABR SupMin();
  bool inclusN(ABR);
  bool inclusR(ABR);
};

ABR Pair(int n);

ABR Nbres(int n);

void SortieLatex(ABR Ar, std::string filepath);

#endif