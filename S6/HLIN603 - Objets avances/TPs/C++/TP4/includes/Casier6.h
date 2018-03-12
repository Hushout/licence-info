#ifndef CASIER6_H
#define CASIER6_H

class Bouteille{
public:
	Bouteille();
	virtual ~Bouteille();
};

class Oeuf{
public:
	Oeuf();
	virtual ~Oeuf();
};

template <typename T>
class Casier6
{
private:
	T* cases[6];

public:
	Casier6();
	virtual ~Casier6();
	virtual void range(T* elt, int numeroCase);
};

#include "Casier6.cc"

#endif