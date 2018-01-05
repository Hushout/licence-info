#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <stdint.h>
#include "matrice.h"

class Piece : public Matrice{

 private:

  int _x;
  int _y;
    
 public: 
  
  Piece();
  Piece(size_t hauteur, size_t largeur, size_t x = 0, size_t y = 0);
  Piece(const Piece& P);
  Piece& operator=(const Piece& P);
  ~Piece();

  //Accesseur en ecriture:
  void setX(int x);
  void setY(int y);
  void setXY(int x, int y);

  //Accesseur en lecture:
  int X() const {return _x;}
  int Y() const {return _y;}

  //Verifie si le format de la piece rentre dans la Matrice
  bool fitIn(const Matrice& M);
  
  //Verifie si la piece est entierement dans la Matrice à la position (x, y)
  bool fitInAt(int x, int y, const Matrice& M);

  //Verifie si la piece peut etre placée dans la Matrice (uniquement sur des 0)
  bool canPlaceAtPos(const Matrice& M);

    //Verifie si la piece peut etre placée dans la Matrice a la position choisis
  bool canPlaceAt(int x , int y , const Matrice& M);

  //Verifie si il existe une position dans la Matrice où la piece peut etre placée.
  bool aUnePlace(const Matrice& M);

  //Place la piece dans la Matrice
  void placeIn(Matrice& M);

  //Charge un piece aleatoirement à partir d'un fichier
  void loadRand(const std::string nomFichier);

  //Sauvegarde une piece dans un fichier
  void savePiece(const std::string nomFichier);

  //Charge une Piece à partir d'un fichier
  //numPiece sert si plus d'une Piece est sauvegardée
  //numPiece = 0 charge la premiere Piece sauvegardée etc..
  void loadPiece(const std::string nomFichier, size_t numPiece);

  bool operator==(const Piece&);
};

//renvoie une graine qui change constamment pour la fonction aleatoire
int randomSeed();

//Donne le nombre de tours du processeur depuis le demarrage (pour aleatoire)
uint64_t rdtsc(); 

#endif
