#include <iostream>

using namespace std;

Bouteille::Bouteille(){
	cout << "je suis une Bouteille" << endl;
}

Bouteille::~Bouteille(){}

Oeuf::Oeuf(){
	cout << "je suis un Oeuf" << endl;
}

Oeuf::~Oeuf(){}

template <typename T>
Casier6<T>::Casier6(){
	for (int i=0; i<6; i++) 
		cases[i]=NULL;
}

template <typename T>
Casier6<T>::~Casier6(){}

template <typename T>
void Casier6<T>::range(T* elt, int numeroCase){
	cases[numeroCase] = elt;
}