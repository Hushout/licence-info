#include <iostream>
#include "CompteBancaire.h"

using namespace std;

int main(int argc, char const *argv[])
{
	CompteBancaire* CB = new CompteBancaire(200);
	CompteRemunere* CR = new CompteRemunere(200);
	CompteDepot* CD = new CompteDepot(200);
	CompteDepotRemunere* CDR = new CompteDepotRemunere(200);

	delete CB;
	delete CR;
	delete CD;
	delete CDR;

	return 0;
}