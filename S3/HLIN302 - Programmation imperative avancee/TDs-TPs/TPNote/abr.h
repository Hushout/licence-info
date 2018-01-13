#include <iostream>
#include <fstream>

template <typename T>
class Noeud{

 private:
  T val;
  Noeud<T>* succG;
  Noeud<T>* succD;

 public:

  Noeud(const T&);
  Noeud(const Noeud<T>&);
  ~Noeud();
  
  Noeud<T> &operateur=(const Noeud<T>&);

  T getVal() const{return val;}
  Noeud<T>* getSuccG() const {return succG;}
  Noeud<T>* getSuccD() const {return succD;}
  
  void setVal(const T& v);
  void setGauche(Noeud* g);
  void setDroit(Noeud* d);
  
  void affiche();
};

template <typename T>
class ABR {
 private:
  Noeud<T>* N;
  
 public:
  ABR();
  ABR(const ABR& A);
  ~ABR();


  void load(char* fichier);
  void insert(const T& v);
  int  find(const T&) const; // return the position of the element or -1
  void affiche();
};

template <typename T>
Noeud<T>* creerNoeud(const T& v);


#include "abr.tcc"
