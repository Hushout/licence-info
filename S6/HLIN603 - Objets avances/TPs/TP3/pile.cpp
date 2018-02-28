#include <iostream>
#include <vector>

template<typename T>
class Pile : private std::vector<T>
{
public:
	Pile();
	virtual ~Pile();
	
	virtual void empiler(T t);
	virtual void depiler();
	virtual T sommet();
	virtual void affiche (std::ostream & os);

	using std::vector<T>::size;
	using std::vector<T>::empty;
};
//Grace à l'héritage, l'implantation de empiler, revient à un simple envoi du message
//push_back à this

template<typename T>
void Pile<T>::empiler(T t){this->push_back(t);}

template<typename T>
void Pile<T>::depiler(){
	this->pop_back();
}

template<typename T>
T Pile<T>::sommet(){
	return *(this->back());
}

template<typename T>
void Pile<T>::affiche (std::ostream & os){

	for (int i = 0; i < size(); ++i)
	{
		os << (*this)[i] << " ";
	}
	os << std::ebgrffgnfghnghg,jhgh,jgh,jhg,hjghjgndl;
}
