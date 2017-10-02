#ifndef MATRICE_H
#define MATRICE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

class Matrice{

 private:
  
  int** _matrice;
  size_t _hauteur;
  size_t _largeur;

 public:

  Matrice();
  Matrice(size_t hauteur, size_t largeur);
  Matrice(const Matrice& M);
  Matrice& operator=(const Matrice& M);
  ~Matrice();

  //Alloue le tableau à 2 dimension et initialise toutes ses valeurs à 0
  void alloc(size_t hauteur, size_t largeur);

  //Desalloue le tableau à 2 dimensions
  void free();

  //copy la Matrice M en allouent une nouvelle Matrice
  void copy(const Matrice& M);

  //Accesseur en ecriture:
  void setVal(size_t i, size_t j, int val);
  void setHauteur(size_t hauteur);
  void setLargeur(size_t largeur);

  //Remplace toutes les valeurs de la ligne ou de la colonne par val 
  void setLigne (size_t i, int val);
  void setColonne(size_t j, int val);

  //Accesseur en lecture:
  int at(size_t i, size_t j) const;
  size_t getHauteur() const {return _hauteur;}
  size_t getLargeur() const {return _largeur;}

  //Verifie si la valeur val est dans la Matrice
  bool isIn(int val) const;

  //Affiche la Matrice dans le terminal
  void print();

  //Sauvegarde la grille dans un fichier
  void save(const std:: string nomFichier);

  //Charge la Matrice à partir d'un fichier
  //numPiece sert si plus d'une Matrice est sauvegardée
  //numPiece = 0 charge la premiere Matrice sauvegardée etc..
  void load(const std::string nomFichier, size_t numPiece);

  bool operator==(const Matrice&);
};

//Renvoie la position du separateur (="-") choisie avec numSep dans un fichier
int posSeparateur(const std::string nomfichier, size_t numSep);

//Ecrit la Matrice dans un flux
void write(std::ostream &flux, const Matrice& M);

//Ecrit la Matrice à partir d'un flux
void read(std::istream &flux, Matrice& M);


////////////////// SURCHARGE /////////////////////////
//////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Matrice& M);

std::istream &operator>>(std::istream &is, Matrice& M);

#endif
