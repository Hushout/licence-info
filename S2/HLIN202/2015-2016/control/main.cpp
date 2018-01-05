#include <iostream>

using namespace std;

// EXERCICE 1

string voyelles(string T);
bool estVoyelle(char C);
int *diviseurs(int n);

bool estVoyelle(char C)
{
    return ((C == 'a') || (C == 'e') || (C == 'i') || (C == 'o') || (C == 'u') || (C == 'y'));
}


string voyelles(string T)
{
    string res;
    int k = 0;

    for(int i = 0 ; i < (signed)(T.size()) ; i++)
    {
        if(estVoyelle(T[i]))
        {
            res.push_back(T[i]);
            k++;
        }
    }
    return res;
}


int *diviseurs(int n)
{
    int tailleTab = 0;

    for(int i = 0 ; i < n ; i++)
    {
        if(n % i == 0)
        {
            tailleTab++;
        }
    }

    int *tab = new int[tailleTab];
    int k = 0;

    for(int i = 0 ; i < n ; i++)
    {
        if(n % i == 0)
        {
            tab[k] = i;
            k++;
        }
    }
    return tab;
}


// EXERCICE 2


struct photo
{
    int taille;
    int numero;
    int nbpixelsH;
    int nbpixelsV;
};

struct album
{
    int nbr;
    photo * contenu;
};


photo saisiePhoto();

void affichePhoto(photo P);
int tailleAlbum(album A);
void afficheAlbum(album A);
void saisiePointeurPhoto(photo * P);
void saisiePointeurAlbum(album * A);


photo saisiePhoto()
{
    photo res;
    char c;
    cout << "Quelle est le numero de votre photo ? " << endl;
    cin >> res.numero;
    cout << "Quelle est le format de votre photo ? (EX: 800x600 " << endl;
    cin >> res.nbpixelsH >> c >> res.nbpixelsV;
    cout << "Combien d'octet fait votre photo ? " << endl;
    cin >> res.taille;
    cout << endl;
    return res;
}

void affichePhoto(photo P)
{
    cout << "Photo n°" << P.numero << endl;
    cout << "Taille du fichier : " << P.taille << endl;
    cout << "Résolution : " << P.nbpixelsH << "x" << P.nbpixelsV << endl;
    cout << "/////////////" << endl;
}



int tailleAlbum(album A)
{
    int compteur = 0;

    for(int i = 0 ; i < A.nbr ; i++)
    {
        compteur = compteur + (A.contenu[i]).taille ;
    }
    compteur = compteur / 1000000 ;
    return compteur;
}



void afficheAlbum(album A)
{
    for(int i = 0 ; i < A.nbr ; i++)
    {
        affichePhoto(A.contenu[i]);
    }
}

void saisiePointeurPhoto(photo * P)
{
    char c;
    cout << "Quelle est le format de votre photo ? (EX: 800x600 " << endl;
    cin >> P->nbpixelsH >> c >> P->nbpixelsV;
    cout << "Combien d'octet fait votre photo ? " << endl;
    cin >> P->taille;
    cout << endl;

}

void saisiePointeurAlbum(album * A)
{
    cout << "Combien de photos possede votre album ?" << endl;
    cin >> A->nbr;
    cout << endl;

    A->contenu = new photo[A->nbr];

    for(int i = 0 ; i < A->nbr ; i++)
    {
        cout << "Ajout de la photo N°" << i << endl;
        cout << "////////////////////" << endl;
        cout << endl;

        saisiePointeurPhoto(&(A->contenu[i]));
        A->contenu[i].numero = i;
    }
}

int main()
{
    album A;
    saisiePointeurAlbum(&A);
    afficheAlbum(A);
    return 0;
}
