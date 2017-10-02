// Fichier dans lequel vous écrirez les fonctions que l'on vous demandera de définir

#include "listesEtTableaux.cpp"

  bool triangleEqui(int a, int b, int c){
    return(a == b && b == c);
  }

  bool triangle(int a, int b, int c){
    return(a <= b+c && b <= a+c && c <= a+b);
  }

  bool triangleRectangle(int a, int b, int c){
    return(a*a == b*b+c*c || b*b == a*a+c*c || c*c == a*a+b*b);
  }

  bool triangleIso(int a, int b, int c){
    return( a == b || a == c || b ==c);
  }

  bool ouExcl(bool a, bool b){
    return(a != b);
  }

  bool multiple(int a, int b){
    return(a % b == 0);
  }

  bool estPair(int n)
  {
    return(n==0 ? true : !estPair((abs(n-1))));
  }

bool existeMul11(int a, int b)
{
  return(multiple(a, 11) ? true : ( a==b ? false : existeMul11(a+1, b)));
}
 
int nbChifDec(int a)
{
  return(a < 10 ? 1 : (1 + (nbChifDec(a/10))));
} 

int chifrang(int n, int k)
{
  return(k == 1 ? n%10 : chifrang(n/10, k));
}

int mystere(int n)
{
  int v;
  v = (53+n);
  v = (2*v);
  v = (v-99);
  v = ((v/2)-n);
  return v;
}

int sompair(int n)
{
  int som = 0;
  for(int i = 1 ; i <= n ; i++)
    som = som + 2*i;
  return som;
}

int somimpair(int n)
{
  int som = 0;
  for(int i = 1 ; i <= n ; i++)
    som = som + 2*i -1;
  return som;
}

int somdiv(int n)
{
  int som = 0;
  for(int i = 1 ; i <= n ; i++)
    {
      if((n % i) == 0)
	{ 
	  som = som + i;
	}
    }
  return som;     
}

bool estparfait(int n)
{
 return somdiv(n) == n*2 ? true : false;
}

bool existeparfait(int a, int b)
{
  int conteneurdetrue = 0;

  for(int i = a ; i <= b ; i++)
    {
      if(estparfait(i) == true)
	{
	  conteneurdetrue++;
	}
    } 
  return conteneurdetrue > 0;
}

int parfaitsuivant(int n)
{
  int i = n;
  while(estparfait(i) != true)
    {
      i++;
    }
  return i;
}

int emeparfait(int n)
{
  int i = 0;
  int compteurdeparfait = 0;

  while(compteurdeparfait <= n)
    {
      i = 1+ parfaitsuivant(i);
      compteurdeparfait++;
    }
  return i-1;
}


















