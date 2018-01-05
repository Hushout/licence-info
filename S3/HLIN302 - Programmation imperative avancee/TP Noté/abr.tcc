//////////////////////////  Noeud  ///////////////////////////
//////////////////////////////////////////////////////////////

template <typename T>
Noeud<T>::Noeud() {
  val = 0;
  gauche = NULL;
  droit = NULL;
}


template <typename T>
Noeud<T>::Noeud(const T& v, const Noeud& g, const Noeud& d) {
  val = v;
  gauche = g;
  droit = d;
}

template <typename T>
Noeud<T>::~Noeud() {
  delete gauche;
  delete droit;
}

template <typename T>
T Noeud<T>::getVal() const{
  return val;
}

template <typename T>
Noeud<T>* Noeud<T>::getGauche() const{
  return gauche;
}

template <typename T>
Noeud<T>* Noeud<T>::getDroit() const{
  return droit;
}

template <typename T>
void Noeud<T>::setVal(const T& v){
  val = v;
}

template <typename T>
void Noeud<T>::setGauche(Noeud* g){
  gauche = g;
}

template <typename T>
void Noeud<T>::setDroit(Noeud* d){
  droit = d;
}

template <typename T>
void Noeud<T>::affiche(){
  std::cout << getVal() << std::endl;
}

//////////////////////////  ABR  /////////////////////////////
//////////////////////////////////////////////////////////////

template <typename T>
ABR<T>::ABR() {
  N = NULL;
}

template <typename T>
ABR<T>::ABR(const ABR& A) {
  N->val = A->val;
  N->gauche = A->gauche;
  N->droit = A->droit;
}

template <typename T>
ABR<T>::~ABR() {
  delete N;
}

template <typename T>
void ABR<T>::insert(const T& v) {
  if(N == NULL){
    N = creerNoeud(v);
  }
  else if(N->getVal() < v){
    N->setGauche(creerNoeud(v));
  }
  else{
    N->setDroit(creerNoeud(v));
  }
}

/*
template <typename T>
void ABR<T>::load(char* fichier) {
  std::ifstream fic(fichier, ios::in); 
}
*/


template <typename T>
void ABR<T>::affiche() {
  std::cout << N->getVal() << std::endl;
  std::cout << (N->getGauche())->getVal() << std::endl;
  std::cout << (N->getDroit())->getVal() << std::endl;
}










template <typename T>
Noeud<T>* creerNoeud(const T& v){
  Noeud<T>* N = new Noeud<T>;
  N->setVal(v);
  return N;
}
