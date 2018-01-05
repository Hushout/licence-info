// Fichier dans lequel vous écrirez les fonctions que l'on vous demandera de définir

#include "listesEtTableaux.cpp"

// Fonction moyenne
// Données: a : nombre, b : nombre
// Résultat: Nombre, la moyenne de a et b

float moyenne(float a, float b)
{
  return (a+b)/2;
}

//Fonction max3
//Données: a: nombre, b: nombre, c:nombre
//Résultat: Nombre, le plus grand nombre entre a, b et c

float max3(float a, float b, float c)
{
  return((a>b)?((a>c)?a:c):((b>c)?b:c));
}

//Fonction multiple
//Données: a: nombre, b: nombre
//Résultat: true si a est un multiple de b, false sinon.

bool multiple(int a, int b)
{
  return(b==0?(a==0?true:false):((a%b==0)?true:false));
}

//Fonction triangleEqui
//Données: a: nombre, b: nombre, c: nombre
//Résultat: true si a, b et c sont de mêmes longueurs, false sinon

bool triangleEqui(float a, float b, float c)
{
  return(a==b?(b==c?true:false):false);
}

//Fonction triangle
//Données: a: nombre, b: nombre, c: nombre
//Résultat: true si a, b et c sont les longueurs des côtés d'un triangle, false sinon

bool triangle(float a, float b, float c)
{
  return((a+b)>c?((b+c)>a?((a+c)>b?true:false):false):false);
}

//Fonction triangleRect
//Données: a: nombre, b: nombre, c: nombre
//Résultat: true si a, b et c sont les longueurs des côtés d'un triangle rectangle, false sinon

bool triangleRect(float a, float b, float c)
{
  return((pow(a,2)+pow(b,2)==pow(c,2)?true:(pow(b,2)+pow(c,2)==pow(a,2)?true:(pow(a,2)+pow(c,2)==pow(b,2)?true:false))));
}

//Fonction triangleIso
//Données: a: nombre, b: nombre, c: nombre
//Résultat: true si a, b et c sont les longueurs des côtés d'un triangle isocèle, false sinon

bool triangleIso(float a, float b, float c)
{
  return(a==b?(b==c?false:(a==c?false:true)):(b==c?(a==c?false:true):(a==c?true:false)));
}

//Fonction ouExcl
//Données: a: booléen, b: booléen
//Résultat: true si parmi a et b, un seul des 2 est true, false sinon

bool ouExcl(bool a, bool b)
{
  return(a==b?false:(a==true?true:(b==true?true:false)));
}

//Fonction mul2ou3
//Données: a: nombre
//Résultat: true si n est multiple de 2 ou de trois mais pas de 6, false sinon

bool mul2ou3(int a)
{
  return(multiple(a,6)?false:(ouExcl(multiple(a,2),multiple(a,3))));
}

//Fonction memeDizaine
//Données: a: nombre, b: nombre
//Résultat: true si a et b sont dans la même dizaine, false sinon

bool memeDizaine(int a, int b)
{
  return(a%b<10?true:(b%a<10?true:false));
}

//Fonction memeParite
//Données: a: nombre, b: nombre
//Résultat: true si les nombres sont tout les deux pairs ou impairs, false sinon

bool memeParite(int a, int b)
{
  return(a%2==0?(b%2==0?true:false):(b%2==0?false:true));
}

//Fonction gainRoulette
//Données: a: nombre, b: nombre, c: nombre
//Résultat: 20 fois a si b=c, 5 fois a si b et c sont dans la même dizaine, 2 fois a si b et c sont tout les deux pairs ou impairs, sinon 0

int gainRoulette(int a, int b, int c)
{
  return(b==c?20*a:(memeDizaine(b,c)?5*a:(memeParite(b,c)?2*a:0)));
}

//Fonction estPair
//Données: a: nombre
//Résultat: true si a est pair, false sinon

bool estPair(int a)
{
  return(a>=0?(a==0?true:!estPair(a-1)):(a==0?true:!estPair(a+1)));
}

//Fonction existeMul11
//Données: a: nombre, b: nombre
//Résultat: true si il existe un multiple de 11 dans l'intervalle [a;b], false sinon

bool existeMul11(int a, int b)
{
  return(a<=b?(a==b?(b%11==0?true:false):(a%11==0?true:existeMul11(a+1,b))):false);
}

//Fonction maxMul11
//Données: a: nombre, b: nombre
//Résultat: le plus grand entier de l'intervalle [a;b] multiple de 11, -1 si il n'y en a pas

int maxMull11(int a, int b)
{
  return(b>a?(b%11==0?b:maxMull11(a,b-1)):(a%11==0?a:-1));
}

//Fonction nbMull11
//Données: a: nombre, b: nombre
//Résultat: le nombre d'entiers multiples de 11 dans [a;b]

int nbMul11(int a, int b)
{
  return(a<=b?(a%11==0?1+nbMul11(a+1,b):nbMul11(a+1,b)):(b%11==0?1:0));
}

//Fonction somMul11
//Données: a: nombre, b: nombre
//Résultat: somme des entiers multiples de 11 dans l'intervalle [a;b]

int somMul11(int a, int b)
{
  return(a<=b?(a%11==0?a+somMul11(a+1,b):somMul11(a+1,b)):0);
}

//Fonction nbChifDec
//Données: n: nombre
//Résultat: le nombre de chiffres de l'écriture décimale de n

int nbChifDec(int n)
{
  return(n>=0 && n<=9?1:1+nbChifDec(n/10));
}

//Fonction chifRang
//Données: n: nombre, k: nombre 
//Résultat: le chiffre de rang k de l'écriture décimale de n

int chifRang(int n, int k)
{
  return(k==1?n%10:chifRang((n/10),(k-1)));
}

//Fonction somChif
//Données: n: nombre
//Résultat: la somme des des chiffres de n

int somChif(int n)
{
  return(nbChifDec(n)>1?chifRang(n,1)+somChif(n/10):n);
}

//Fonction racNum
//Données: n: nombre
//Résultat: la racine numérique de n

int racNum(int n)
{
  return(nbChifDec(n)<=1?n:racNum(somChif(n)));
}

//Fonction invChif
// Données: n: nombre
//Résultat: le nombre dont l'écriture décimale est celle de n lue en sens inverse

int invChif(int n)
{
  return(n>=0 && n<=9?n:chifRang(n,1)*pow(10,nbChifDec(n)-1)+invChif(n/10));
}

//Fonction existeRac
//Données: n: nombre, k: nombre
//Résultat: true si n admet une racine entière supérieure ou égale à l'entier k, sinon false

bool existeRac(int n, int k)
{
  return(k<n?(k*k==n?true:existeRac(n,k+1)):false);
}

//Fonction estCarre
//Données: n: nombre 
//Résultat: true si n admet une racine entière, sinon false

bool estCarre(int n)
{
  return(n==0?true:existeRac(n,1));
}

//Fonction longLi
//Données: Li une liste d'entiers
//Résultat: le nombre d'éléments de li

int longLi(list<int>li)
{
  return(estVide(li)?0:1+longLi(queue(li)));
}

//Fonction minLi
//Données: Li une liste d'entiers
//Résultat: le plus petit élément de li

int minLi(list<int>li)
{
  return(estVide(queue(li))?tete(li):(tete(li)<minLi(queue(li))?tete(li):minLi(queue(li))));
}

//Fonction oterLi
//Données: n: nombre, Li une liste d'entiers
//Résultat: Li sans le premier élément de valeur n, li si il n'y en a pas

list<int>oterLi(int n, list<int>li)
{
  return(estVide(queue(li))?(tete(li)==n?liVide<int>():li):(tete(li)==n?queue(li):cons(tete(li),oterLi(n,queue(li)))));
}

//Fonction estTriee
//Données: Li une liste d'entiers
//Résultat: true si li est triée par ordre croissant, sinon false

bool estTriee(list<int>li)
{
  return(estVide(li)?true:(estVide(queue(li))?true:(tete(li)<=tete(queue(li))?estTriee(queue(li)):false)));
}

//Fonction triListe
//Données: Li une liste d'entiers
//Résultat: la liste constituée des éléments de li dans l'ordre croissant

list<int>triListe(list<int>li)
{
  return estVide(li)?li:
    estVide(queue(li))?li:
    cons(minLi(li),triListe(oterLi(minLi(li),li)));
}

//Fonction lgPrefEg
//Données: Li une liste d'entiers non vide
//Résultat: le chiffre correspondant à la longueur du plus long préfixe de li constitué d'éléments tous égaux

int lgPrefEg(list<int>li)
{
  return li == liVide<int>()?0:
    tete(li)==tete(queue(li))?1+lgPrefEg(queue(li)):1;
}

//Fonction supPrefEg
//Données: Li une liste d'entiers non vide
//Résultat: le plus long suffixe de li dont le 1er élément, s'il existe, est différent de la tete de li

list<int>supPrefEg(list<int>li)
{
  return li == liVide<int>()?liVide<int>():
    queue(li) == liVide<int>()?liVide<int>():
    tete(li)==tete(queue(li))?supPrefEg(cons(tete(li),queue(queue(li)))):oterLi(tete(li),li);
}

//Fonction supRepet
//Données: Li une liste d'entiers 
//Résultat: li sans répétition d'éléments consécutifs égaux

list<int>supRepet(list<int>li)
{
  return li == liVide<int>()?liVide<int>():
    lgPrefEg(li)>1?cons(tete(li),supRepet(supPrefEg(li))): //PROBLEME ERREUR (Core Dumped)
    cons(tete(li),supRepet(queue(li)));
}

//Fonction codeLi
//Données: Li une liste d'entiers
//Résultat: li codé selon le principe: chaque séquence d'éléments consécutifs égaux est remplacé par la longueur de la séquence et la valeur de l'élément 
//répété

list<int>codeLi(list<int>li)
{
  return  lgPrefEg(li)==1?cons(1,cons(tete(li),codeLi(supPrefEg(li)))):
    cons(lgPrefEg(li),cons(tete(li),codeLi(supPrefEg(li))));
}

//Fonction decodeLi
//Données: Li une liste d'entiers
//Résultat: li décodé selon le principe de codeLi

//list<int>decodeLi(list<int>li)
//{
//  return tete(li)==1?cons(tete(queue(li)),decodeLi(queue(queue(li))):
//			  lgPrefEg(li)<2?cons(tete(queue(li)),li):
//			  lgPrefEg(li)==


//tete(supRefEg(li))?decodeLi(queue(queue(supRefEg(li)))):cons(tete(queue(li)),decodeLi(li))
