#include <iostream>
ctime
using namespace std;

bool estPair(int n);
void fct1(int * tab, int taille, int * nbImpair, int * premierImp, int * dernierImp);

int aleatoire()
{

    return nbAleatoire = rand() % 5
}


bool estPair(int n)
{
    return n % 2 == 0;
}

int * fct2(n);
{
    int * tab = new int[n]

    for(int i = 0 ; i < n ; i++)
    {
        tab[i] = aleatoire();
    }
    return tab;
}

void fct1(int * tab, int taille, int * nbImpair, int * premierImp, int * dernierImp)
{
    *nbImpair = 0;
    int nbTour = 0;

    for(int i = 0; i < taille ; i++)
    {
        if(!estPair(tab[i]))
        {
            *nbImpair = (*nbImpair + 1);

            if(nbTour == 0)
            {
                    *premierImp = i;
                    nbTour++;
            }
        }
    }

    int k = 0;

    for(int i = 0; i < taille ; i++)
    {
        if(!estPair(tab[i]))
        {
            if(k == *nbImpair - 1)
            {
                *dernierImp = i;
            }

            k++;
        }
    }
}


int main()
{
    int taille = 5, nbImpair, premierImp, dernierImp;
    int * tab = new int[5];
    tab[0] = 4;
    tab[1] = 1;
    tab[2] = 2;
    tab[3] = 3;
    tab[4] = 7;

    fct1(tab, taille, &nbImpair, &premierImp, &dernierImp);

    int * res = new int[nbImpair];

    for(int i = premierImp ; i < taille ; i++)
    {

    }


    cout << nbImpair << " " << premierImp << " " << dernierImp << endl;

    return 0;
}


