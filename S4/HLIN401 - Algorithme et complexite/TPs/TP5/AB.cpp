//AB.cpp

#include "AB.h"


Sommet::Sommet(Valeur v){
  racine = v;
  Pere = NULL;
  SAG = NULL;
  SAD = NULL;
  FGP = false;
}

Sommet::Sommet(Sommet& s){

  racine = s.racine;
  FGP = s.FGP;
  
  if(s.SAG != NULL){
    SAG = new Sommet(*s.SAG);
    SAG->FGP = true;
    SAG->Pere = this;
  }
  if(s.SAD != NULL){
    SAD = new Sommet(*s.SAD);
    SAD->FGP = false;
    SAD->Pere = this;
  }
}

bool Sommet::FeuilleP(){
  if(SAG == NULL && SAD == NULL){
    return 0;
  }
  else{
    return 1;
  }
}

void Sommet::SupprimerSAG(){
  SAG->Pere = NULL;
  SAG->FGP = false;
  SAG = NULL;
}

void Sommet::SupprimerSAD(){
  SAD->Pere = NULL;
  SAD->FGP = false;
  SAD = NULL;
}

void Sommet::GrefferSAG(AB g){
  if(g != NULL){
    g->Pere = this;
    g->FGP = true;
    SAG = g;
  }
  else {
	SAG = NULL;  
  }
}

void Sommet::GrefferSAD(AB d){
  if(d != NULL){
    d->Pere = this;
    d->FGP = false;
    SAD = d;
  }
  else {
	SAD = NULL;  
  }
}

void Sommet::RemplacerPourLePerePar(AB Ar){
  if(Pere != NULL){
    if(FGP){
      Pere->GrefferSAG(Ar);
    }
    else{
      Pere->GrefferSAD(Ar);
    }
  }
}





