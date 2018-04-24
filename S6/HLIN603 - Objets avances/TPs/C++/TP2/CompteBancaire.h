class CompteBancaire
{
protected:
	float solde;
public:
	CompteBancaire();
	CompteBancaire(float s);
	virtual ~CompteBancaire();
};

class CompteRemunere : public CompteBancaire
{
public:
	CompteRemunere();
	CompteRemunere(float s);
	virtual ~CompteRemunere();
};

class CompteDepot : public CompteBancaire
{
public:
	CompteDepot();
	CompteDepot(float s);
	virtual ~CompteDepot();
};

class CompteDepotRemunere : virtual public CompteDepot, virtual public CompteRemunere
{
public:
	CompteDepotRemunere();
	CompteDepotRemunere(float s);
	virtual ~CompteDepotRemunere();
};