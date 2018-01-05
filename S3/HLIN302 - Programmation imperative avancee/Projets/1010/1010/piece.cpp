#include "piece.h"

Piece::Piece() : Matrice(){
  setXY(0, 0);
}

Piece::Piece(size_t hauteur, size_t largeur, size_t x, size_t y) : Matrice(hauteur, largeur){
  setXY(x, y);
}

Piece::Piece(const Piece& P) : Matrice(P){
  setXY(P.X(), P.Y());
}


Piece& Piece::operator=(const Piece& P){
  copy(P);
  setXY(P.X(), P.Y());
  return *this;
}

Piece::~Piece(){
}

void Piece::setX(int x){
  _x = x;
}

void Piece::setY(int y){
  _y = y;
}

void Piece::setXY(int x, int y){
  setX(x);
  setY(y);
}

bool Piece::fitIn(const Matrice& M){
  int positionAbsMaxY = getHauteur() + Y();
  int positionAbsMaxX = getLargeur() + X();

  return (positionAbsMaxY <= (int) M.getHauteur() &&
	  positionAbsMaxX <= (int) M.getLargeur() && Y() >= 0 && X() >= 0);
}

bool Piece::fitInAt(int x, int y, const Matrice& M){
  int positionAbsMaxY = getHauteur() + y;
  int positionAbsMaxX = getLargeur() + x;

  return (positionAbsMaxY <= (int) M.getHauteur() &&
	  positionAbsMaxX <= (int) M.getLargeur() &&  y >= 0 && x >= 0);
}

bool Piece::canPlaceAtPos(const Matrice& M){

  int positionAbsMaxY = getHauteur() + Y();
  int positionAbsMaxX = getLargeur() + X();
  
  if(fitIn(M)){
    for(int i = 0 ; i < (int)M.getHauteur() ; i++){
      for(int j = 0 ; j < (int)M.getLargeur() ; j++){
	if((i >=  Y() && j >= X()) && (i < positionAbsMaxY && j < positionAbsMaxX)){
	  if(M.at(i, j) != 0 && at(i-Y(), j-X()) != 0){
	    return false;
	  }
	}
	else if(i >=  positionAbsMaxY && j >= positionAbsMaxX){
	  return true;
	}
      }
    }
    
    return true;
  }
  return false;
}


bool Piece::canPlaceAt(int x , int y , const Matrice& M){

  int positionAbsMaxY = getHauteur() + y;
  int positionAbsMaxX = getLargeur() + x;
  
  if(fitInAt(x , y , M)){
    for(int i = 0 ; i < (int)M.getHauteur() ; i++){
      for(int j = 0 ; j < (int)M.getLargeur() ; j++){
	if((i >=  y && j >= x) && (i < positionAbsMaxY && j < positionAbsMaxX)){
	  if(M.at(i, j) != 0 && at(i-y, j-x) != 0){
	    return false;
	  }
	}
	else if(i >=  positionAbsMaxY && j >= positionAbsMaxX){
	  return true;
	}
      }
    }
    return true;
  }
  return false;
}

bool Piece::aUnePlace(const Matrice& M){
  for(size_t i =0 ; i<M.getHauteur() ; i++){
    for(size_t j=0; j<M.getLargeur() ;  j++){
      if(canPlaceAt( j , i , M)){return true;}
    }
  }
  return false ;
}

void Piece::placeIn(Matrice& M){

  int positionAbsMaxY = getHauteur() + Y();
  int positionAbsMaxX = getLargeur() + X();
  
  if(fitIn(M)){
    
    for(int i = 0 ; i < (int)M.getHauteur() ; i++){
      for(int j = 0 ; j < (int)M.getLargeur() ; j++){
	if((i >=  Y() && j >= X()) && (i < positionAbsMaxY && j < positionAbsMaxX)){
	  if(at(i-Y(), j-X()) != 0){
	    M.setVal(i, j, at(i-Y(), j-X()));
	  }
	}
      }
    }
  }
}

void Piece::loadRand(const std::string nomFichier){
  
  std::ifstream fichier(nomFichier.c_str());

  if(!fichier){
    std::cout << "ERREUR: Dans loadRand, Impossible ouvrir fichier" << std::endl;
  }

  else{
    std::string ligne;
    int nbPiece = 0;
    int numPiece = 0;

    //initialisation de la fonction aleatoire avec le nb tours du processeur
    srand(randomSeed()); 
  
    while(getline(fichier, ligne)){
      if(ligne == "-"){
	nbPiece++;
      }
    }
    fichier.close();

    //donne un nombre de piece aleatoire
    numPiece  = rand() % nbPiece;
    load(nomFichier, numPiece);
  }
}

void Piece::savePiece(const std::string nomFichier){
  
  std::ofstream os(nomFichier.c_str(), std::ios::app);

  if(!os){
    std::cout << "ERREUR: Dans savePiece, Impossible ouvrir fichier" << std::endl;
  }
  else{
    os << X() << " " << Y() << std::endl;
    save(nomFichier);
    os.close();
  }
}

void Piece::loadPiece(const std::string nomFichier, size_t numPiece){

  std::ifstream fichier(nomFichier.c_str());

  if(!fichier){
    std::cout << "ERREUR: Dans loadPiece, Impossible ouvrir fichier" << std::endl;
  }
  else{
    std::string ligne;
    std::vector<int> v;
    int val = 0;
    int x = 0, y = 0, k = 0;
    int hauteur = 0;
    int largeur = 0;
    bool finMat = false;

    fichier.seekg(posSeparateur(nomFichier, numPiece) , std::ios::beg);
    
    getline(fichier, ligne);
    std::istringstream isstreamXY(ligne);
    isstreamXY >> x;
    isstreamXY >> y;
	
    while(getline(fichier, ligne) && !finMat){
      std::istringstream isstream(ligne);

      if(ligne == "-"){
	finMat = true;
      }
      else{
	while((isstream >> val)){
	  v.push_back(val);
	  if(hauteur == 0){
	    largeur++;
	  }
	}
	hauteur++;
      }
    }

    Piece P(hauteur, largeur, x, y);

    for(size_t i = 0 ; i < P.getHauteur() ; i++){
      for(size_t j = 0 ; j < P.getLargeur() ; j++){
	P.setVal(i, j, v[k]);
	k++;
      }
    }
    copy(P);
    setXY(x, y);
    fichier.close();
  }
}

bool Piece::operator==(const Piece& M1){

  if(M1.X() == X() && M1.Y() == Y()){

    if(M1.getHauteur() == getHauteur() &&
       M1.getLargeur() == getLargeur()){
    
      for(size_t i = 0 ; i < M1.getHauteur() ; i++){
	for(size_t j = 0 ; j < M1.getLargeur() ; j++){
	  if(M1.at(i, j) != at(i, j)){
	    return false;
	  }
	}
      }
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

int randomSeed(){return rdtsc();}

//  Windows
#ifdef _WIN32
#include <intrin.h>
uint64_t rdtsc(){
    return __rdtsc();
}

//  Linux/GCC
#else
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
#endif
