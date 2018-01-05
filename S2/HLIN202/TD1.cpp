#include <iostream>
#include <cmath>

using namespace std;

int absolu();
int sommeProd100();
int sommeProdPairs100();
int test();
float racine2();




int main()
{
    sommeProd100();
    return 0;
}

int test()
{
    cout <<sqrt(5)<< endl;

    return 0;
}

int absolu()
{
    int n;
    cout << "Entrez un entier: ";
    cin >> n;
    if(n < 0) n=-n;
    cout <<"Sa valeur absolu est: "<< n << endl;
    return 0;
}

int sommeProd100()
{

    int som = 0;
    int prod = 1;

    for(int i=1 ; i<=100 ; i++)
    {
        som+=i;
        cout <<"Somme chiffres i: "<< i << endl;
        prod*=i;
    }
    cout <<"Somme chiffres 1->100: "<< som << endl;
    cout <<"Produit chiffres 1->100: "<< prod << endl;

    return 0;
}

int sommeProdPairs100()
{

    int som = 0;
    int prod = 2;

    for(int i=2 ; i<=100 ; i+=2)
    {
        som+=i;
        cout <<"Somme chiffres i: "<< i << endl;
        prod*=i;
    }
    cout <<"Somme chiffres 1->100: "<< som << endl;
    cout <<"Produit chiffres 1->100: "<< prod << endl;

    return 0;
}

float racine2()
{




    int n = 1;
    while(n != 0)
    {
        cout << "Entrez une valeur: ";
        cin >> n;
        if(n > 0)
            cout << "La racine de " << n << " est: " << sqrt(n) << endl << endl;
        if(n < 0)
            cout << "Operation Impossible avec des nombres negatifs"<< endl << endl;
    }
    cout << "Fin du programme" << endl;
    return 0;
}





