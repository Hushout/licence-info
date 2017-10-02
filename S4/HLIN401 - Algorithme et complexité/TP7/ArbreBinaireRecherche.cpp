#include "ArbreBinaireRecherche.h"

SommetABR::SommetABR(Valeur v){
  racine = v;
  Pere = NULL;
  SAG = NULL;
  SAD = NULL;
  FGP = false;
}

SommetABR::SommetABR(SommetABR& s){

  racine = s.racine;
  FGP = s.FGP;
  
  if(s.SAG != NULL){
    SAG = new SommetABR(*s.SAG);
    SAG->FGP = true;
    SAG->Pere = this;
  }
  if(s.SAD != NULL){
    SAD = new SommetABR(*s.SAD);
    SAD->FGP = false;
    SAD->Pere = this;
  }
}

bool SommetABR::FeuilleP(){
  return (SAG == NULL && SAD == NULL);
}

void SommetABR::SupprimerSAG(){
  SAG->Pere = NULL;
  SAG->FGP = false;
  SAG = NULL;
}

void SommetABR::SupprimerSAD(){
  SAD->Pere = NULL;
  SAD->FGP = false;
  SAD = NULL;
}

void SommetABR::GrefferSAG(ABR g){
  if(g != NULL){
    g->Pere = this;
    g->FGP = true;
    SAG = g;
  }
  else{
	SAG = NULL;
  }
}

void SommetABR::GrefferSAD(ABR d){
  if(d != NULL){
    d->Pere = this;
    d->FGP = false;
    SAD = d;
  }
  else{
	SAD = NULL;
  }
}

void SommetABR::RemplacerPourLePerePar(ABR Ar){
  if(Pere != NULL){
    if(FGP){
      Pere->GrefferSAG(Ar);
    }
    else{
      Pere->GrefferSAD(Ar);
    }
  }
}

///////////////////////////////////// ABR ////////////////////////////////////

ABR SommetABR::PlusPetit(){
  
  if(SAG){
    return SAG->PlusPetit();
  }
  return this;
}

ABR SommetABR::RechercherValeur(Valeur v){
  
  if(racine == v){
    return this;
  }
  else if(racine > v){
    
    if(SAG){
      return SAG->RechercherValeur(v);
    }
    else{
      return NULL;
    }
  }
  else{
    if(SAD){
      return SAD->RechercherValeur(v) ;
    }
    else {
      return NULL;
    }
  }
}

void SommetABR::InsererValeur(Valeur v){

  if (racine >= v) {

    if(SAG) {
      SAG->InsererValeur(v);
    }
    else {
      GrefferSAG(new SommetABR(v));
    }
  }
  else {
    
    if (SAD) {
      SAD->InsererValeur(v);
    }
    else {
      GrefferSAD(new SommetABR(v));
    }
  }
}

ABR SommetABR::SupMin(){
  if(!SAG) {
    
    if(Pere) {
      RemplacerPourLePerePar(SAD) ;
      return SAD;
    }
  }
  ABR min = PlusPetit();
  min->RemplacerPourLePerePar(min->SAD) ;
  return this;
}


ABR SommetABR::SupprimerValeur(Valeur v){
  ABR R = RechercherValeur(v);
  
  if (!R) {
    return this;
  }
  if(R->FeuilleP()) {
    if(!R->Pere) {
      return NULL;
    }
    R->RemplacerPourLePerePar(NULL);
    return this;
  }
  if(!R->SAG) { 
	if (R->Pere) {
	  R->RemplacerPourLePerePar(R->SAD); 
	  return this;
	}
	else {
	  R->SAD->Pere=NULL; 
	  return R->SAD;
	} 
  }
  if(!R->SAD) { 
	if(R->Pere) {
	  R->RemplacerPourLePerePar(R->SAG); 
	  return this;
	}
	else {
		R->SAG->Pere=NULL;
		return R->SAG;
	} 
  }
  R->racine = R->SAD->PlusPetit()->racine;
  R->SAD->SupMin();
  return this;
}

bool SommetABR::inclusN(ABR A){
	
	ABR R = A->RechercherValeur(racine);
	
	if(R){
		
		if(SAD && SAD){
			return SAG->inclusN(A) && SAD->inclusN(A);
		}
		else if(SAD){
			return SAD->inclusN(A);
		}
		else if(SAG){
			return SAG->inclusN(A);
		}
		else {
			return true;
		}
	}
	else{
		return false;
	}
}

/* compiler avec g++ main.cpp ArbreBinaireRecherche.cpp SortieLatex.cpp  */
