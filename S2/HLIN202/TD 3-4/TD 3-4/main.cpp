#include <iostream>
#include <cmath>

using namespace std;

float moyenne(int n);
void testMoyenne();

void test();

int nbChiffreDec(int n);
int chifRang(int n, int k);

int cubeChiffreNombre(int n);
bool estSommeCubeChifre(int n);
int nbCubeChiffreNombre(int interval);

bool estPair(int n);
void afficheEtoile(int nbEspace, int nbEtoile);
void triangleEtoile(int baseTriangle);

int main()
{
    triangleEtoile(79);
    return 0;
}

void test()
{
    cout << 5 << endl;
}

//EX 6

void testMoyenne()
{
    int nbNote;
    cout << "Combien de notes ? ";
    cin >> nbNote;
    cout << endl;
    cout << "la moyenne est : " << moyenne(nbNote) << endl;
}

float moyenne(int n)
{
    float som = 0;
    int note = 0;

    for(int i = 1 ; i <= n ; i++)
    {
        cout << "Entrez la note N°" << i << ": ";
        cin >> note;
        cout << endl;
        som += note;
    }

    return som/n;
}

//EX 7


int nbChiffreDec(int n){
    return (n / 10) == 0 ? 1 : (1 + nbChiffreDec(n / 10));
}

int chifRang(int n, int k){
    return k == 1 ? n % 10 : chifRang(n/10, k-1);
}

int cubeChiffreNombre(int n){
    int res = 0;
    for(int i = 1 ; i <= nbChiffreDec(n) ; i++)
    {
        res = res + (int)pow(chifRang(n, i), 3);
    }
    return res;
}

bool estSommeCubeChifre(int n){
    return n == cubeChiffreNombre(n);
}

int nbCubeChiffreNombre(int interval){
    int nbFonctionne = 0;
    for(int i = 2 ; i <= interval ; i++)
    {
        if(estSommeCubeChifre(i))
        {
            cout << "Ce nombre fonctionne: " << i << endl;
            nbFonctionne++;
        }
    }
    return nbFonctionne;
}


//EX 9

bool estPair(int n){
    return n % 2 == 0;
}

void afficheEtoile(int nbEspace, int nbEtoile){

    for(int i = 0 ; i < nbEspace ; i++)
    {
        cout << " ";
    }

    for(int i = 0 ; i < nbEtoile ; i++)
    {
        cout << "*";
    }
    cout << endl;
}

void triangleEtoile(int baseTriangle){

    int i = 1, k = 0;

    if(estPair(baseTriangle))
    {
        baseTriangle--;
    }

    while (baseTriangle >= i)
    {
        if(!estPair(i))
        {
            afficheEtoile((baseTriangle/2)-k, i);
            i+=2;
            k++;
        }
    }
}







