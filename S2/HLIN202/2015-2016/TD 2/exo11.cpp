#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    float erreur, somme ;
    int signe, denom;

    somme = 0 ;
    signe = 1 ;
    denom = 1 ;

    cout << "Erreur max autoriser ?" ;
    cin >> erreur;

    while((float)1 / denom  > erreur)
    {
    somme = somme + (float)signe * 1 / denom;
    signe = -signe;
    denom +=2;
    }

    cout << "Approximation : " << somme << endl;

	return 0;
}
