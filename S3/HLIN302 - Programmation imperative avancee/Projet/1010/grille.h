#ifndef GRILLE_H
#define GRILLE_H

#include "window.h"
#include "piece.h"

class Grille : public Matrice{

 private:

  Piece _piece;

 public:
  
  Grille();
  Grille(int haut, int larg);
  Grille(int haut, int larg, Piece& P);
  Grille(int haut, int larg, int pieceX, int pieceY, const std::string ficP);
  Grille(Grille& G);
  Grille& operator=(Grille& G);
  ~Grille();

  //Accesseur en ecriture:
  void setPiece(const Piece& P);
  void setPieceXY(int x, int y);
  
  //Accesseur en lecture:
  Piece& getPiece() {return _piece;}

  //Deplace la piece de +x et +y
  void movePiece(int x, int y);

  //Place la piece dans la grille
  void placePiece(){ _piece.placeIn(*this);}

  //Verifie si le format de la piece rentre dans la grille
  bool pieceFit(){return _piece.fitIn(*this);}

  //Verifie si la piece est entierement dans la grille à la position (x, y)
  bool pieceFitAt(int x, int y){return _piece.fitInAt(x, y, *this);}

  //Verifie si la piece peut etre placée dans la grille (uniquement sur des 0)
  bool canPlacePiece(){return _piece.canPlaceAtPos(*this);}

  //Repositione la piece dans la matrice si en dehors
  void makePieceFit();

  //Charge un piece au hasard
  void loadPieceRand(const std::string nomFichier){_piece.loadRand(nomFichier);}

  //Sauvegarde la grille dans un fichier
  void saveGrille(const std::string nomFichier);

  //Charge grille à partir d'un fichier
  //numGrille sert si plus d'une grille est sauvegardée
  //numGrille = 0 charge la premiere grille sauvegardée etc
  void loadGrille(const std::string nomFichier, int numGrille);


  bool operator==(Grille&);
};

//Converti un int en Color
Color intToCol(int valCol);

//Affiche un carré de format H:2*taille, L:2*taille dans une fenetre
void printCell(Window& W, int x, int y, int valCol, int taille = 4);

//Affiche une Matrice dans une fenetre de format H:2*taille, L:2*taille
void printMat(Window& W, const Matrice& M, int taille = 4);
void printMat(Window& W, const Matrice& M, int x, int y, int taille = 4);


//Affiche une Piece dans une fenetre de format H:2*taille, L:2*taille
void printPiece(Window& W, Piece& P, int taille = 4);

//Affiche une Grille dans une fenetre de format H:2*taille, L:2*taille
void printGrille(Window& W, Grille& G, int taille = 4);

#endif
