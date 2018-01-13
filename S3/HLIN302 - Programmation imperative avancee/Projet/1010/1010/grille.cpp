#include "grille.h"

Grille::Grille() : Matrice(){}

Grille::Grille(int haut, int larg) : Matrice(haut, larg){}

Grille::Grille(int haut, int larg, Piece& P) : Matrice(haut, larg){
  this->setPiece(P);
}

Grille::Grille(int haut, int larg, int pieceX, int pieceY, const std::string ficP) : Matrice(haut, larg){
  this->setPieceXY(pieceX, pieceY);
  this->loadPieceRand(ficP);
}

Grille::Grille(Grille& G) : Matrice(G){
  this->setPiece(G.getPiece());
}

Grille& Grille::operator=(Grille& G){
  this->copy(G);
  this->setPiece(G.getPiece());
  return *this;
}


Grille::~Grille(){
  
}

void Grille::setPiece(const Piece& P){
  _piece = P;
}

void Grille::setPieceXY(int x, int y){
  _piece.setXY(x, y);
}

void Grille::movePiece(int x, int y){

  int nouvX = _piece.X() + x;
  int nouvY = _piece.Y() + y;

  //Empeche la piece de sortir de la Grille

  if(pieceFitAt(nouvX, nouvY)){
    _piece.setXY(nouvX, nouvY);
  }
}

void Grille::makePieceFit(){
  int x = _piece.X();
  int y = _piece.Y();
  
  while(!pieceFit()){
    if((int)(_piece.X() + _piece.getLargeur()) > (int)(getLargeur())){	
      x--;
    }
    else if((int)(_piece.Y() + _piece.getHauteur()) > (int)(getHauteur())){	
      y--;
    }
    else if(_piece.X() < 0){	
      x++;
    }
    else if(_piece.Y() < 0){	
      y++;
    }
    else{
      x = getLargeur()/2;
      y = getHauteur()/2;
    }
    _piece.setXY(x, y);
  }
}

void Grille::saveGrille(const std::string nomFichier){
  
  std::ofstream os(nomFichier.c_str(), std::ios::app);

  if(!os){
    std::cout << "ERREUR: Dans savePiece, Impossible ouvrir fichier" << std::endl;
  }
  else{
    save(nomFichier);
    _piece.savePiece(nomFichier);
    os.close();
  }
}

void Grille::loadGrille(const std::string nomFichier, int numPiece){
  load(nomFichier, numPiece);
  _piece.loadPiece(nomFichier, numPiece+1);
}

bool Grille::operator==(Grille& G){
  return (*this == G) && (this->getPiece() == G.getPiece());
}


Color intToCol(int valCol){
  if(valCol == 0){
    return WBLACK;
  }
  else if(valCol == 1){
    return BCYAN;
  }
  else if(valCol == 2){
    return WBLUE;
  }
  else if(valCol == 3){
    return WGREEN;
  }
  else if(valCol == 4){
    return WYELLOW;
  } 
  else if(valCol == 5){
    return WRED;
  }
  else if(valCol == 6){
    return WMAGENTA;
  }
  else{
    return BCYAN;
  }
}

void printCell(Window& W, int x, int y, int valCol, int taille){

  int yMax = y + (1*taille);
  int xMax = x + (2*taille);
  
  for(int i = y ; i < yMax ; i++){
    for(int j = x ; j < xMax ; j++){
      W.print(j, i, ' ', intToCol(valCol));
    }
  }
}

void printMat(Window& W, const Matrice& M, int taille){
  
  for(int i = 0 ; i < (int) M.getHauteur() ; i++){
    for(int j = 0 ; j < (int) M.getLargeur() ; j++){
      if(M.at(i, j) >= 0){
	printCell(W, 2*taille*j, taille*i, M.at(i, j), taille);
      }
    }
  }
}

void printMat(Window& W, const Matrice& M, int x, int y, int taille){ 
  int Ymax = M.getHauteur() + y;
  int Xmax = M.getLargeur() + x;
  
  for(int i = y ; i < Ymax ; i++){
    for(int j = x ; j < Xmax ; j++){
      if(M.at(i - y, j - x) != 0){
	printCell(W, 2*taille*j, taille*i, M.at(i - y, j - x), taille);
      }
    }
  }
}


void printPiece(Window& W, Piece& P, int taille){ 
  int Ymax = P.getHauteur() + P.Y();
  int Xmax = P.getLargeur() + P.X();
  
  for(int i = P.Y() ; i < Ymax ; i++){
    for(int j = P.X() ; j < Xmax ; j++){
      if(P.at(i - P.Y(), j - P.X()) != 0){
	printCell(W, 2*taille*j, taille*i, 6, taille);
      }
    }
  }
}

void printGrille(Window& W, Grille& G, int taille){
  printMat(W, G, taille);
  printPiece(W, G.getPiece(), taille); 
}
