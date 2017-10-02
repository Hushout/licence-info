#include <iostream>

using namespace std;

bool estimpair(int n);
void afficheEtoile(int n);
void afficheVoid();
void arbre();

int main()
{
    while(1)
	arbre();

	return 0;
}


	bool estimpair(int n)
	{
	return n % 2 != 0;
	}


	void afficheEtoile(int nbEspaces, int nbEtoiles)
	{
        for(int i = 0 ; i < nbEspaces ; i++)
		{
			cout << " ";
		}

		for(int i = 0 ; i < nbEtoiles ; i++)
		{
			cout << "*";
		}
		cout << endl;
	}


	void arbre()
	{

	int nbEtoiles = 0;
	int nbTours;
	int nbEspaces;

		while(!estimpair(nbEtoiles))
		{
			cout << "entrez un nombre impair" << endl;
			cin >> nbEtoiles;
		}

		nbTours = nbEtoiles;
		nbEspaces = nbEtoiles / 2;
		nbEtoiles = 1;

        for(int x = 0 ; x < nbTours ; x++)
        {
            afficheEtoile(nbEspaces, nbEtoiles);

            nbEspaces--;
            nbTours--;
            nbEtoiles+=2;
        }
	}

