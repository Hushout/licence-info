#include <iostream>

using namespace std;

// EXERCICE 6

struct s_point{
    char nom;
    int x, y;
};

void saisiePoint(s_point * P);
void affichePoint(s_point P);
void maz(s_point * P);
bool estLettre(string S);

bool estLettre(char * S){
    return sizeof(S) == 1;
}

void saisiePoint(s_point * P){

    cout << "Entrez le nom du point : ";
    cin >> P->nom;
    cout << "Entrez sa position :"<< endl;
    cout << "X = ";
    cin >> P->x;
    cout << "Y = ";
    cin >> P->y;
    cout << endl;
}

void affichePoint(s_point * P){
    cout << "Point " << P->nom << " de coordonnées (" << P->x << ", " << P->y << ")"<< endl;
}

void maz(s_point * P){
    P->nom = '0';
    P->x = 0;
    P->y = 0;
}

s_point oppose(s_point P){
    s_point res = {'A' + 'Z' - P.nom, -P.x, -P.y};
    return res;
}


// EXERCICE 9


struct cellule{
    int contenu;
    cellule * suivant;
};

struct pile{
    int cardinal;
    cellule * premier;
};

pile pileVide();
int cardPile(pile P);
bool estVide(pile P);
void empiler(pile * P);

pile pileVide(){

}

int cardPile(pile P){

}

bool estVide(pile P){

}

void empiler(pile * P){

}

int main()
{
    s_point P;
    saisiePoint(&P);
    affichePoint(&P);
    maz(&P);
    affichePoint(&P);
    return 0;
}
