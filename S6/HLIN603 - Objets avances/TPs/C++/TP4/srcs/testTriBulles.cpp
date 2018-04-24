#include <iostream>

using namespace std;

template <typename Elt>
void echange(Elt& e1, Elt& e2){
	Elt aux=e1; e1=e2; e2=aux;
}

template <typename Elt>
void triBulles(Elt T[], int tailleT)
{
	int i=tailleT-2,j; bool ech=true;
	while (i>=0 && ech)
	{
		ech=false;
		for (j=0; j<=i; j++){
			if (T[j]>T[j+1]){
				echange(T[j],T[j+1]); ech=true;
			}
		}
		i--;
	}
}

int	main(){

	string tab[] = {"aaa", "eee", "fff", "bbb", "ccc"};

	triBulles<string>(tab, 5);

	for (int i = 0; i < 5; ++i)
	{
		cout << tab[i] << " ";
	}
	cout << endl;
	return  0;
}


