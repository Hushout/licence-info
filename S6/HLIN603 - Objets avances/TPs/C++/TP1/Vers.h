#ifndef vers_h
#define vers_h

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

class Vers
{
private:
	std::string suiteMots;
	std::string rime;

public:
	Vers();
	Vers(std::string s);
	Vers(std::string s, std::string r);
	virtual ~Vers();
	
	virtual std::string getSuiteMots() const;
	virtual void setSuiteMots(std::string s);
	virtual std::string getRime() const;
	virtual void setRime(std::string r);

	virtual void saisie(std::istream& is);
	virtual void affiche(std::ostream& os);
};

#endif