#include "Tas.h"

bool estPair(int n)
{
  return n % 2 == 0;
}

ArbreParfait::ArbreParfait(int n){
  IndicePremierSommetLibre = 0;
  NombreMaximalDeSommets = n;
  contenu = new Valeur[n];
}


int ArbreParfait::AjouteSommetArbreParfait(Valeur v){
  if(IndicePremierSommetLibre < NombreMaximalDeSommets){
    contenu[IndicePremierSommetLibre] = v;
    IndicePremierSommetLibre++;
    return 1;
  }
  else{
    
    return -1;
  }
}

void ArbreParfait::Echanger(indiceSommet a,indiceSommet b){

  int tmp = contenu[a];
  contenu[a] = contenu[b];
  contenu[b] = tmp;
}

void ArbreParfait::SupprimerDansArbreParfait(indiceSommet indice){
  // 0 < indice < IndicePremierSommetLibre
  Echanger(indice, IndicePremierSommetLibre - 1);
  IndicePremierSommetLibre--;
}

bool ArbreParfait::SommetValide(indiceSommet i){
  return (i >= 0) && (i < IndicePremierSommetLibre);
}

int ArbreParfait::Racine(){
  return contenu[0];
}

///
bool ArbreParfait::FeuilleP(indiceSommet i){
  return SommetValide(i) &&
	  !SommetValide(FilsGauche(i)) &&
	  !SommetValide(FilsGauche(i));
}
///

indiceSommet ArbreParfait::Pere(indiceSommet i){
  return i == 0 ? 0 : estPair(i) ? i/2 - 1 : i/2;
}

indiceSommet ArbreParfait::FilsGauche(indiceSommet i){
  return i*2 + 1;
}

indiceSommet ArbreParfait::FilsDroit(indiceSommet i){
  return i*2 + 2;
}

void ArbreParfait::SupprimerArbreParfait(indiceSommet i){
  if(i == 0){
    IndicePremierSommetLibre = 0;
  }
  else if(FeuilleP(i)){
    SupprimerDansArbreParfait(i);
  }
  else{
    if(SommetValide(FilsDroit(i))){
      SupprimerArbreParfait(FilsDroit(i));
    }
    if(SommetValide(FilsGauche(i))){
      SupprimerArbreParfait(FilsGauche(i));
    }
    SupprimerDansArbreParfait(i);
  }
}

/////////////////////// TAS //////////////////////////

Tas::Tas(int n) : ArbreParfait(n) {} 

void Tas::Remonter(indiceSommet i){
  if(i > 0 && SommetValide(i)){
    if(contenu[i] < contenu[Pere(i)]){
      Echanger(i, Pere(i));
      Remonter(Pere(i));
    }
  }
}

void Tas::Descendre(indiceSommet i){
  if(!FeuilleP(i)){
    
    if(SommetValide(FilsDroit(i))){
      
      if(contenu[i] > contenu[FilsGauche(i)] || contenu[i] > contenu[FilsDroit(i)]){
	
		if(contenu[FilsGauche(i)] <= contenu[FilsDroit(i)]){
		  Echanger(i, FilsGauche(i));
		  Descendre(FilsGauche(i));
		}
		else{
		  Echanger(i, FilsDroit(i));
		  Descendre(FilsDroit(i));
		}
      }
    }
    else{
      if(contenu[i] > contenu[FilsGauche(i)]){
		Echanger(i, FilsGauche(i));
		Descendre(FilsGauche(i));
      }
    }
  }
}

void Tas::SupprimerTas(indiceSommet i){
  SupprimerDansArbreParfait(i);
  Descendre(i);
}

void Tas::AjouterTas(Valeur v){
  AjouteSommetArbreParfait(v);
  Remonter(IndicePremierSommetLibre-1);
}

AB Tas::TasVersABRec(indiceSommet i){
  
  if(SommetValide(i)){
    AB A = new Sommet(contenu[i]);

    if(SommetValide(FilsGauche(i))){
	A->GrefferSAG(TasVersABRec(FilsGauche(i)));
    }
    if(SommetValide(FilsDroit(i))){
	A->GrefferSAD(TasVersABRec(FilsDroit(i)));
    }
    return A;
  }
}

AB Tas::TasVersAB(){
  return TasVersABRec(0);
}
