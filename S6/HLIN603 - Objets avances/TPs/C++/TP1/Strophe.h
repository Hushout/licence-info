#ifndef strophe_h
#define strophe_h

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include "Vers.h"

class Strophe
{
private:
	Vers** suiteVers;
	int nbVers;
public:
	Strophe();
	
	virtual ~Strophe();
	
	virtual void saisie(std::istream& is);
	virtual Vers* vers(int n) const;
	virtual void affiche(std::ostream& os);
};

#endif