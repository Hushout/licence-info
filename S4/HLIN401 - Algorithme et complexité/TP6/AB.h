//AB.h

#ifndef AB_H
#define AB_H

#include <iostream>
#include <sstream>

typedef int Valeur;

class Sommet;

typedef Sommet* AB;

  std::string* TikzRecursAB(int ligne,int gauche, int droite, int numeroPere, int typeFils, AB Ar);

class Sommet {
  
  public:
  Valeur racine;
  AB Pere, SAG, SAD;
  bool FGP;

  public:
  Sommet(Valeur v);
  Sommet(Sommet& s);

  void GrefferSAG(AB g);
  void GrefferSAD(AB d);
  void SupprimerSAG();
  void SupprimerSAD();

  bool FeuilleP();

  void RemplacerPourLePerePar(AB);

   friend std::string* TikzRecursAB(int ligne,int gauche, int droite, int numeroPere, int typeFils, AB Ar);
};
void SortieLatex(AB Ar, std::string filepath);


#endif
