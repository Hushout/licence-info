// Fichier dans lequel vous écrirez les fonctions que l'on vous demandera de définir

#include "listesEtTableaux.cpp"

// Fonction moyenne
// Données: a : nombre, b : nombre
// Résultat: Nombre, la moyenne de a et b

bool estPair(int n)
{
  return
  n==0 ? true :
  !estPair(abs(n)-1);
}

bool existeMul11(int a, int b)
{
  return
  (a%11 == 0 || b%11 == 0) && (a <= b) ? true :
  (a!=b)  && (a < b) ? existeMul11(min(a,b), max(a,b)-1) : false;
}

int maxMul11(int a, int b)
{
  return
  !existeMul11(a,b) ? -1 :
  existeMul11(b,b) ? b : maxMul11(a,b-1);
}

int nbMul11(int a, int b)
{
  return
  !existeMul11(a,b) ? 0 :
  existeMul11(b,b) ? nbMul11(a,b-1)+1 : nbMul11(a,b-1);
}

int somMul11(int a, int b)
{
  return
  !existeMul11(a,b) ? 0 :
  existeMul11(b,b) ? somMul11(a,b-1)+b : somMul11(a,b-1);
}

int nbChifDec(int n)
{
  return n == 0 ? 0 : nbChifDec(n/10)+1;
}

int chifRang(int n, int k)
{
  return
  k == 1 ? n%10 : 
  chifRang(n/10, k-1);
}

int somChif(int n)
{
  return
  nbChifDec(n) <= 1 ? n : 
  somChif(n/10) + chifRang(n, 1) ;
}

int racNum(int n)
{
  return nbChifDec(n) <= 1 ? n : racNum(somChif(n));
}

int invChif(int n)
{
  return
  nbChifDec(n) <= 1 ? n : 
  invChif(n/10) + chifRang(n, 1)*pow(10, (nbChifDec(n)-1));
}

bool existeRac(int n, int k)
{
  return k*k == n ? true : k*k < n ? existeRac(n, k+1) : false;
}

bool estCarre(int n)
{
  return existeRac(n, pow(n,float (1/2)));
}












