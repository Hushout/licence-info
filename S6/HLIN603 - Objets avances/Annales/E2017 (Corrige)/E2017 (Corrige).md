# Question 1:

``` c++
#include <iostream>
#include <vector>

using namespace std;

class IAttraction {

public:
	virtual ~IAttraction() = 0;

	virtual int getDuree() = 0;
	virtual string getDescriptif(){return "attraction";}
};

//Comme nous n'avons pas implementer le destructeur, cette objet reste egalement abstrait.
class Attraction : public IAttraction {

private:
	string descriptif;
	int duree;

public:
	Attraction() : descriptif(), duree() {}
	Attraction(string descriptif, int duree) : descriptif(descriptif), duree(duree) {}

	int getDuree(){return this->duree;}
	string getDescriptif(){return this->descriptif;}

};

//Ici on a implémenter le destructeur ce qui rend l'objet concret.
class AttractionAnimalière : public Attraction {

private:
	string nomAnimaux;

public:
	AttractionAnimaliere() : Attraction(), nomAnimaux() {}
	Attraction(string descriptif, int duree, string nomAnimaux) : Attraction(descriptif, duree), nomAnimaux(nomAnimaux) {}

	~AttractionAnimaliere(){}

	string getDescriptif(){return Attraction::getDescriptif() + " " + this->nomAnimaux;}
};

template <typename T>
class ParcLoisirs {

private:
	string nom;
	vector<T> listeAttractions;

public:
	ParcLoisirs() : nom(parcland), listeAttractions() {}

	bool existeDescription(string d){
		for(int i = 0 ; i < (int)listeAttractions.size() ; i++){
			if(listeAttractions[i].getDescriptif().equals(d))
				return true;
		} 
		return false;
	}

	void ajoute(T a){
		if(!this->existeDescriptif(a.getDescriptif()))
			listeAtractions.push_back(a);
	}

	double dureeMoyAttr(){
		return
	}

	void transfere(ParcLoisirs<T> autreParc){
		for(int i = 0 ; i < (int)autreParc.size() ; i++){
			this->ajoute(autreParc[i]);
		} 
	}
};

int main(int argc, char** argv){

	AttractionAnimaliere* a1 = new AttractionAnimaliere("zoo", 14, "zebres"); 
	AttractionAnimaliere* a2 = new AttractionAnimaliere("rando", 15, "chevaux"); 
	
	ParcLoisirs<Attraction*>* parc1 = new ParcLoisirs<Attraction*>();
	parc1->ajoute(a1);	parc1.ajoute(a2);

	ParcLoisirs<IAttraction*>* parc2 = new ParcLoisirs<Attraction*>();
	parc2->transfere(parc1);

	cout << parc2.dureeMoyAttr() << endl;

	delete parc1;
	delete parc2;
}
```

# Question 2:


