#include "Vers.h"

using namespace std;

Vers::Vers(){}

Vers::Vers(string s){
	suiteMots = s;
}

Vers::Vers(string s, string r){
	suiteMots = s;
	rime = r;
}

Vers::~Vers(){}

std::string Vers::getSuiteMots() const{
	return suiteMots;
}

void Vers::setSuiteMots(string s){
	suiteMots = s;
}

std::string Vers::getRime() const{
	return rime;
}

void Vers::setRime(std::string r){
	rime = r;
}


void Vers::saisie(std::istream& is){
	cout << "vers puis rime" << endl;
	is >> suiteMots >> rime;
}

void Vers::affiche(std::ostream& os){
	os << "<<" << suiteMots << ">>";
}

