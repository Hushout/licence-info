#include "matrice.h"

Matrice::Matrice(){
  alloc(1, 1);
}

Matrice::Matrice(size_t hauteur, size_t largeur){
  alloc(hauteur, largeur);
}

Matrice::Matrice(const Matrice& M){
  copy(M);
}

Matrice& Matrice::operator=(const Matrice& M){
  copy(M);
  return *this;
}

Matrice::~Matrice(){
  free();
}

void Matrice::alloc(size_t hauteur, size_t largeur){
  _matrice = new int*[hauteur];

  for(size_t i = 0 ; i < hauteur ; i++){
    _matrice[i] = new int[largeur];
  }

  for(size_t i = 0 ; i < hauteur ; i++){
    for(size_t j = 0 ; j < largeur ; j++){
      setVal(i, j, 0);
    }
  }

  setHauteur(hauteur);
  setLargeur(largeur);
}

void Matrice::free(){
  for(size_t i = 0 ; i < getHauteur() ; i++){
    delete[] _matrice[i]; 
  }
  delete[] _matrice;

  setHauteur(0);
  setLargeur(0);
}

void Matrice::copy(const Matrice& M){
  setHauteur(M.getHauteur());
  setLargeur(M.getLargeur());

  alloc(M.getHauteur(), M.getLargeur());
    
  for(size_t i = 0 ; i < M.getHauteur() ; i++){
    for(size_t j = 0 ; j < M.getLargeur() ; j++){
      setVal(i, j, M.at(i, j));
    }
  }
}

void Matrice::setVal(size_t i, size_t j, int val){
  _matrice[i][j] = val;
}

void Matrice::setLigne(size_t i, int val){
  size_t j = 0;
  while(j < getLargeur()){
    setVal(i, j, val);
    j++;
  }
}

void Matrice::setColonne(size_t j, int val){
  size_t i = 0;
  while(i < getHauteur()){
    setVal(i, j, val);
    i++;
  }
}

int Matrice::at(size_t i, size_t j) const{
  return _matrice[i][j];
}


void Matrice::setHauteur(size_t hauteur){
  _hauteur = hauteur;
}
void Matrice::setLargeur(size_t largeur){
  _largeur = largeur;
}

bool Matrice::isIn(int val) const{
  for(size_t i = 0 ; i < getHauteur() ; i++){
    for(size_t j = 0 ; j < getLargeur() ; j++){
      if(val == at(i, j)){
	return true;
      }
    }
  }
  return false;
}

void Matrice::print(){
  for(size_t i = 0 ; i < getHauteur() ; i++){
    for(size_t j = 0 ; j < getLargeur() ; j++){
      std::cout << at(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

void Matrice::save(std::string nomfichier){

  std::ofstream os(nomfichier.c_str(), std::ios::app);

  if(!os){
    std::cout << "ERREUR: Dans save, Impossible ouvrir fichier" << std::endl;
  }
  else{
    for(size_t i = 0 ; i < getHauteur() ; i++){
      for(size_t j = 0 ; j < getLargeur() ; j++){
	os << at(i, j) << " ";
      }
      os << std::endl;
    }
    os << "-" << std::endl;
  }
  os.close();
}

void Matrice::load(std::string nomfichier, size_t numPiece){

  std::ifstream fichier(nomfichier.c_str());

  if(!fichier){
    std::cout << "ERREUR: Dans load, Impossible ouvrir fichier" << std::endl;
  }
  else{
    std::string ligne;
    std::vector<int> v;
    int val;
    int k = 0;
    int hauteur = 0;
    int largeur = 0;
    bool finMat = false;

    fichier.seekg(posSeparateur(nomfichier, numPiece) , std::ios::beg);

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

    Matrice M(hauteur, largeur);

    for(size_t i = 0 ; i < M.getHauteur() ; i++){
      for(size_t j = 0 ; j < M.getLargeur() ; j++){
	M.setVal(i, j, v[k]);
	k++;
      }
    }
    copy(M);
    fichier.close();
  }
}



bool Matrice::operator==(const Matrice& M1){

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


/////////////////// FONCTION /////////////////////////
//////////////////////////////////////////////////////


void write(std::ostream &os, const Matrice& M){

  for(size_t i = 0 ; i < M.getHauteur() ; i++){
    for(size_t j = 0 ; j < M.getLargeur() ; j++){
      os << M.at(i, j) << " ";
    }
    os << std::endl;
  }
}

void read(std::istream &is, Matrice& M){
  int val = 0;
  for(size_t i = 0 ; i < M.getHauteur() ; i++){
    for(size_t j = 0 ; j < M.getLargeur() ; j++){
      is >> val;
      M.setVal(i, j, val);
    }
  }
}

int posSeparateur(const std::string nomfichier, size_t numSep){
  
  std::ifstream fichier(nomfichier.c_str(), std::ios::app);

  if(!fichier){
    std::cout << "ERREUR: Dans posMatFichier, Impossible ouvrir fichier" << std::endl;
    return -1;
  }
  else{
    std::string ligne;
    bool finMat = false;

    for(size_t i = 0 ; i < numSep ; i++){
      while(!finMat){
	getline(fichier, ligne);
	if(ligne == "-"){
	  finMat = true;
	}
      }
      finMat = false;
    }
    return fichier.tellg();
  }
}


////////////////// AFFICHAGE /////////////////////////
//////////////////////////////////////////////////////


std::ostream &operator<<(std::ostream &os, const Matrice& M){
  write(os, M);
  return os;
}

std::istream &operator>>(std::istream &is, Matrice& M){
  read(is, M);
  return is;
}


