#include <iostream>
#include "CompteBancaire.h"

using namespace std;

CompteBancaire::CompteBancaire() : solde(0) {}

CompteBancaire::CompteBancaire(float s) : solde(s) {}

CompteBancaire::~CompteBancaire() {
	cout << "La banque vous doit " << solde << endl;
}

CompteRemunere::CompteRemunere() : CompteBancaire() {}

CompteRemunere::CompteRemunere(float s) : CompteBancaire(s) {}

CompteRemunere::~CompteRemunere() { 
	solde *= 1.10;
} 

CompteDepot::CompteDepot() : CompteBancaire() {}

CompteDepot::CompteDepot(float s) : CompteBancaire(s) {}

CompteDepot::~CompteDepot() { 
	solde -= 100;
}

CompteDepotRemunere::CompteDepotRemunere() : CompteDepot(), CompteRemunere() {} 

CompteDepotRemunere::CompteDepotRemunere(float s) : CompteDepot(s), CompteRemunere(s) {}

CompteDepotRemunere::~CompteDepotRemunere() {}