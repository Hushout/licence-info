#include "setdepiece.h"

SetDePiece::SetDePiece(){
  
  this->_fichierPiece = "piece.txt";
  this->loadRand();
  this->_indiceP = 0;
}

SetDePiece::SetDePiece(const std::string fichierPiece){
  this->_fichierPiece = fichierPiece;
  this->loadRand();
  this->_indiceP = 0;
}

SetDePiece::~SetDePiece(){

 
}

void SetDePiece::setFichierPiece(const std::string fichier){
  _fichierPiece = fichier;
  loadRand();
}

void SetDePiece::changePiece(){

  if(!toutePiecePlace()){
    
      _indiceP++;
      
      if(_indiceP > 2){
	_indiceP = 0;
      }
      else if(_indiceP < 0){
	_indiceP = 2;
      }

      //Empeche SetDePiece de pointer vers une piece deja Placée
      while(estPlace(_indiceP)){
	_indiceP++;
      
	if(_indiceP > 2){ 
	  _indiceP = 0;
	}
	else if(_indiceP < 0){
	  _indiceP = 2;
	}
      }
      
  }
}

void SetDePiece::markAsPlaced(int indiceP){
  _tabPiece[indiceP] = Piece();
}

bool SetDePiece::estPlace(int indiceP){
  Piece P;
  return _tabPiece[indiceP] == P;
}

bool SetDePiece::toutePiecePlace(){
  return estPlace(0) && estPlace(1) && estPlace(2);
}

void SetDePiece::loadRand(){
  for(int i = 0 ; i < 3 ; i++){
    _tabPiece[i].loadRand(getFichierPiece());
  }
}

void SetDePiece::saveSetDePiece(std::string nomFichier){
  
  std::ofstream os(nomFichier.c_str(), std::ios::app);

  if(!os){
    std::cout << "ERREUR: Dans savePiece, Impossible ouvrir fichier" << std::endl;
  }
  else{
    os << this->getIndicePiece() << std::endl;
    for(int i = 0 ; i < 3 ; i++){
      _tabPiece[i].save(nomFichier);
    }
    os.close();
  }
}

void SetDePiece::loadSetDePiece(std::string nomFichier, int numPiece){

  std::ifstream fichier(nomFichier.c_str());

  if(!fichier){
    std::cout << "ERREUR: Dans loadPiece, Impossible ouvrir fichier" << std::endl;
  }
  else{
    std::string ligne;
    std::vector<int> v;
    int val = 0;
    int x = 0, k = 0;
    int hauteur = 0;
    int largeur = 0;
    bool finMat = false;

    fichier.seekg(posSeparateur(nomFichier, numPiece) , std::ios::beg);
    
    getline(fichier, ligne);
    std::istringstream isstreamXY(ligne);
    isstreamXY >> x;
	
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

    Piece P(hauteur, largeur);

    for(size_t i = 0 ; i < P.getHauteur() ; i++){
      for(size_t j = 0 ; j < P.getLargeur() ; j++){
	P.setVal(i, j, v[k]);
	k++;
      }
    }
    this->_indiceP = x;
    this->_tabPiece[0] = P;
    this->_tabPiece[0].setXY(0, 0);
    fichier.close();
    
    _tabPiece[1].load(nomFichier, numPiece+1);
    _tabPiece[2].load(nomFichier, numPiece+2);
  }
}



