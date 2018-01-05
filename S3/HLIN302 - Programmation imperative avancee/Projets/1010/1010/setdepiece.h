#ifndef SETDEPIECE_H
#define SETDEPIECE_H

#include <iostream>
#include "piece.h"

class SetDePiece {

 private:

  std::string _fichierPiece;
  Piece _tabPiece[3];
  int _indiceP;
   
 public: 
  
  SetDePiece();
  SetDePiece(const std::string fichierPiece);
  ~SetDePiece();

  //Accesseur en ecriture:
  void setFichierPiece(std::string fichier);

  //Accesseur en lecture:
  std::string getFichierPiece() const {return _fichierPiece;}
  int getIndicePiece() const{return _indiceP;}
  Piece getPiece() const{return _tabPiece[_indiceP];}
  Piece at(int i) const{return _tabPiece[i];}

  //Fait pointer l'objet vers la piece suivante
  void changePiece();

  //Charge aleatoirement les pieces du SetDePieces
  void loadRand();

  //Fait considerer au SetDePiece que la piece d'indice indiceP est placée
  void markAsPlaced(int indiceP);

  //Verifie si la piece d'indice indiceP est placée
  bool estPlace(int indiceP);

  //Verifie si toutes les pieces sont placée
  bool toutePiecePlace();

  //Sauvegarde le SetDePiece Dans un fichier
  void saveSetDePiece(std::string nomFichier);

  //Charge SetDePiece à partir d'un fichier
  //numPiece sert si plus d'un SetDePiece est sauvegardé
  //numPiece = 0 charge le premier SetDePiece sauvegardé
  void loadSetDePiece(std::string nomFichier, int numPiece);
};


#endif
