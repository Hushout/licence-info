#include <iostream>

using namespace std;

struct complexe{
    float reel;
    float imaginaire;
};
struct temps{
    int heure;
    int minute;
    float seconde;
};
struct CD{
    int nbPiste;
    temps * duree;
};

void afficheC(complexe c);
void saisieC(complexe* c);
complexe sommeC(complexe c1, complexe c2);
void trucC();
temps conversion(float secondes);
void saisieT(temps *t);
void addTime(temps t1, temps t2, temps * P);
int compareTime(temps t1, temps t2);

void addTime(temps t1, temps t2, temps * P){

}


void saisieC(complexe* c){
    cout << "reel = ";
    cin >> c->reel;
    cout << "imaginaire = ";
    cin >> c->imaginaire;
    cout << endl;
}
void afficheC(complexe c){
    cout << "reel = " << c.reel << endl;
    cout << "imaginaire = " << c.imaginaire << endl;
}
complexe sommeC(complexe c1, complexe c2){
    complexe c3 = {c1.reel + c2.reel, c1.imaginaire + c2.imaginaire};
    return c3;
}
void trucC(){
    complexe c1, c2, c3;
    cout << "Saisie Complexe 1:" << endl;
    saisieC(&c1);
    cout << "Saisie Complexe 2:" << endl;
    saisieC(&c2);

    c3 = sommeC(c1, c2);
    c1 = c3;
    afficheC(c1);
}

//EX 4:

temps conversion(float secondes){
    temps t;
    t.heure = (int) secondes/3600;
    t.minute = ((int) secondes % 3600) / 60;
    t.seconde = secondes - t.heure * 3600 - t.minute * 60;
    return t;
}
void saisieT(temps *t){
    char char1, char2;
    do
    {
        cout << "Entrez un temp sous la forme hh:mm:ss ";
        cout << endl;
        cin >> t->heure >> char1 >> t->minute >> char2 >> t->seconde;
    }
    while(((t->minute < 0) || (t->minute > 59)) || ((t->seconde < 0) || (t->seconde > 59)) || (char1 != ':' || char2 != ':'));
}
void afficheT(temps t){


}

//EX 5:

CD cree(){
    CD cd;
    return cd;
}
void init(CD* cd){

    cout << "Nombre de pistes ?";
    cout << endl;
    cin >> cd->nbPiste;
    cout << "Duree Total ?";

    cd->duree = new temps[cd->nbPiste];

    for(int i = 0 ; i < cd->nbPiste ; i++)
        saisieT(&(cd->duree[i]));
}

void afficheCD(CD cd){

    cout << "Nombre de pistes = " << cd.nbPiste;

    for(int i = 0 ; i < cd.nbPiste ; i++)
    {
        cout << "Duree Total piste " << i << " = ";
        afficheT((cd.duree[i]));
    }
}

temps dureeTotale(CD * cd){

    temps somme = {0, 0, 0};
    for(int i = 0 ; i < cd->nbPiste ; i++)
        addTime(somme, cd->duree[i], &somme);
    return somme;
}

int nbPisteSup(CD * P, float secondes){

    int somme = 0;

    for(int i = 0 ; i < P->nbPiste ; i++)
    {
        if(true)
        somme++;
    }

    return somme;
}


int main()
{
    cout << "tps :" << endl;
    temps t1;
    saisieT(&t1);
    return 0;
}
