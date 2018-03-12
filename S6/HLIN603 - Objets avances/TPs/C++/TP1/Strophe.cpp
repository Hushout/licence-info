#include "Strophe.h"

using namespace std;

Strophe::Strophe(){
	suiteVers = NULL;
	nbVers = 0;
}

Strophe::~Strophe(){
	if(suiteVers) 
		delete[] suiteVers;
}

	
void Strophe::saisie(istream& is){
	if(suiteVers)
		delete[] suiteVers;
	
	cout << "Entrer le nombre de vers : " << endl;
	is >> nbVers; suiteVers = new Vers*[nbVers];

	for (int i = 0; i < nbVers; ++i)
	{
		Vers *v = new Vers();
		v->saisie(is);
		suiteVers[i] = v;
	}
}

Vers* Strophe::vers(int n) const{
	if(n >= 0 && n < nbVers)
		return suiteVers[n];
	else
		return NULL;
}

void Strophe::affiche(ostream& os){
	for (int i = 0; i < nbVers; ++i)
	{
		suiteVers[i]->affiche(os); 
		os << endl;
	}
}
