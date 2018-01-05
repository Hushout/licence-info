#ifndef __CELLULE_H
#define __CELLULE_H
#include <iostream>
#include <string>

class Cellule {
 public:

  enum Couleur {
    NOIR,
    BLEU,
    VERT,
    ROUGE,
    JAUNE,
    NB_COULEURS
  };

 private:
  bool vivante;
  unsigned int x, y;
  Couleur couleur;

 public:

  // Constructeurs
  Cellule(); // morte par défaut
  Cellule(bool etat, unsigned int x, unsigned int y);

  // Accesseurs en lecture
  bool estVivante() const;
  unsigned int getX() const;
  unsigned int getY() const;
  Couleur getCouleur() const;

  // Accesseurs en écriture
  void Vivante(bool etat);
  void setX(unsigned int x);
  void setY(unsigned int y);

  // Autre méthode
  bool estVoisine(const Cellule &c) const;
  void print() const;
};

// Renvoie vrai si la cellule est de la couleur passée en paramètre, faux sinon.
bool CelluleEstDeLaCouleur(const Cellule &cellule, Cellule::Couleur couleur);

// Retourne la chaîne correspondant à la couleur passée en paramètre 
std::string Couleur2String(Cellule::Couleur c);

#endif
