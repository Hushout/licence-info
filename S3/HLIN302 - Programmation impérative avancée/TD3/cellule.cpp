#include "cellule.h"
#include <iostream>
#include <string>
using namespace std;

Cellule::Cellule(): vivante(false), x(0), y(0), couleur(BLEU) {
}

Cellule::Cellule(bool etat, unsigned int x, unsigned int y):
  vivante(etat), x(x), y(y), couleur(etat ? BLEU : NOIR) {
}

bool Cellule::estVivante() const {
  return vivante;
}

unsigned int Cellule::getX() const {
  return x;
}

unsigned int Cellule::getY() const {
  return y;
}

Cellule::Couleur Cellule::getCouleur() const {
  return couleur;
}

// Accesseurs en écriture
void Cellule::Vivante(bool etat) {
  if (etat) {
    couleur = vivante? VERT : BLEU;
  } else {
    couleur = NOIR;
  }
  vivante = etat;
}

void Cellule::setX(unsigned int x) {
  this->x = x;
}

void Cellule::setY(unsigned int y) {
  this->y = y;
}

bool Cellule::estVoisine(const Cellule &c) const {
  return vivante &&
    ((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y) <= 2);
}

void Cellule::print() const {
  std::cout<<"("<<x<<","<<y<<") - > "<<Couleur2String(couleur)<<std::endl;
}

bool CelluleEstDeLaCouleur(const Cellule &cellule, Cellule::Couleur couleur) {
  return (cellule.getCouleur() == couleur);
}

string Couleur2String(Cellule::Couleur c) {
  string res;
  switch (c) {
  case Cellule::NOIR:
    res = "\033[1;30mX\033[0m"; //"noire";
    break;
  case Cellule::BLEU:
    res = "\033[1;34mX\033[0m";//"bleue";
    break;
  case Cellule::VERT:
    res = "\033[1;32mX\033[0m";//"verte";
    break;
  case Cellule::ROUGE:
    res = "\033[1;31mX\033[0m";//"rouge";
    break;
  case Cellule::JAUNE:
    res = "\033[1;33mX\033[0m";//"jaune";
    break;
  default:
    res = "non définie.";
    cerr << "Erreur:" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__
	 << ":Couleur non définie. Les couleurs possibles sont:" << endl;
    for (Cellule::Couleur i = Cellule::NOIR;
	 i != Cellule::NB_COULEURS;
	 i = (Cellule::Couleur) (((int) i)+1)) {
      cerr << "- " << Couleur2String(i) << endl;
    }
  }
  return res;
}
