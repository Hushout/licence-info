#include <iostream>

using namespace std;

int sommeT(int* T, int taille);
void creeTab(int** T, int taille);
void remplitTab(int* T, int taille);
void afficheTab(int* T, int taille);
void matrice(float** M, int i, int j);
int* extract(int* T, int taille, int a, int b);
int* ajoutT(int nb, int* T, int taille);
int *fusionT(int *T1, int taille1, int *T2, int taille2);
void triFusion(int *T, int taille);
void duplicata(int **T, int *taille);
int* concat(int *T1, int taille1, int *T2, int taille2);
int maximum(int *T, int taille);
int *tabPairs(int *T, int taille, int *tailleResultat);
bool estPair(int n);



int main()
{

    int taille = 7, tailleRes = 0;

    int T2[] = {6, 7, 8, 3, 5, 8, 4};
    int *T3;


    T3 = tabPairs(T2, taille, &tailleRes);
    afficheTab(T3, tailleRes);
    return 0;
}

int sommeT(int* T, int taille)
{
    int som = 0;
    for(int i = 0 ; i < taille ; i++)
    {
        som += T[i];
    }
    return som;
}

void creeTab(int** T, int taille)
{
    (*T) = new int[taille];
}

void remplitTab(int* T, int taille)
{
    for(int i = 0 ; i < taille ; i++)
    {
        cout << "Entrer la valeur de T[" << i << "] ";
        cin >> T[i];
    }
}

void afficheTab(int* T, int taille)
{
    cout << "[";
    for(int i = 0 ; i < taille ; i++)
    {
        if(i != taille-1)
        cout << T[i] << ", ";
        else
        cout << T[i];
    }
    cout << "]" << endl;
}


void matrice(float** M, int i, int j)
{
    M = new float* [i];
    for(int x = 0 ; x < i ; x++)
    {
        M[x] = new float[j];
        for(int y = 0 ; y < j ; y++)
            M[x][y] = (float) 1 / (x+y+1);
    }
}

int* extract(int* T, int taille, int a, int b)
{
    int* tab ;
    tab = new int[b-a+1];

    for(int i = 0 ; i < (b-a+1) ; i++)
    tab[i] = T[a+i];

    return tab;
}

int* ajoutT(int nb, int* T, int taille)
{
    int* T2;
    T2 = new int[taille+1];

    for(int i = 0 ; i < taille; i++)
    {

        T2[i] = T[i];

        if(T[i] >= nb)
        {
            T2[i] = nb;
            nb = T[i];
            T2[i+1] = T[i];
        }

    }

    T2[taille] = nb;

    return T2;
}

int *fusionT(int *T1, int taille1, int *T2, int taille2)
{
    int *TRes = NULL, *Ttmp;

    for(int i = 0 ; i < taille1 ; i++)
    {
        Ttmp = ajoutT(T1[i], TRes, i);
        delete[] TRes;
        TRes = Ttmp;
    }

    for(int i = 0 ; i < taille2 ; i++)
    {
        Ttmp = ajoutT(T2[i], TRes, taille1+i);
        delete[] TRes;
        TRes = Ttmp;
    }

    return TRes;
}

void duplicata(int **T, int *taille)
{
    int *TRes;
    int k = *taille;
    TRes = new int[(*taille)*2];

    for(int i = 0 ; i < (*taille) ; i++)
    {
        TRes[i] = (*T)[i];
    }

    for(int i = (*taille)-1 ; i >= 0 ; i--)
    {
        TRes[k] = (*T)[i];
        k++;
    }
    *taille = 2
    *(*taille);
    (*T) = TRes;
}

int *concat(int *T1, int taille1, int *T2, int taille2)
{
    int *TRes;
    int i = 0, k = 0;
    TRes = new int[(taille1 + taille2)];

    while(i < (taille1 + taille2))
    {
        if(i < taille1)
        {
            TRes[i] = T1[i];
            i++;
        }

        else
        {
            TRes[i] = T2[k];
            k++;
            i++;
        }
    }

    return TRes;
}

int maximum(int *T, int taille)
{
    return (taille == 1 ? T[0] :
            max (maximum(&T[0], taille/2), maximum(&T[taille/2], taille-taille/2) ));
}

int *tabPairs(int *T, int taille, int *tailleRes)
{
    int *res, k = 0;
    *tailleRes = 0;

    for(int i = 0 ; i < taille ; i++)
    {
        if(estPair(T[i]) )
        {
            *tailleRes = (*tailleRes) + 1;
        }
    }

    res = new int(*tailleRes);

    for(int i = 0 ; i <= *tailleRes ; i++)
    {
        if( estPair(T[i]) )
        {
            res[k] = T[i];
            k++;
        }
    }

    return res;
}


bool estPair(int n)
{
    return n%2 == 0;
}








