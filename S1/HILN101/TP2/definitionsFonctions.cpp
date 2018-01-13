// Fichier dans lequel vous écrirez les fonctions que l'on vous demandera de définir

#include "listesEtTableaux.cpp"

// Fonction moyenne
// Données: a : nombre, b : nombre
// Résultat: Nombre, la moyenne de a et b


int mystere(int n)
{
int v;
v = 53 + n;
v = 2 * v;
v = v-99;
v = v/2 - n;
return v;
}

int nbRacines(float a,float b,float c)
{
  float discr = b*b - 4*a*c;
  int nbSols = 0;

  if(discr==0){nbSols = 1;}
  else if(discr>0){nbSols = 2;}
  else{nbSols = 0;}

  return nbSols;
}

list<float> solsDegrees2(float a,float b,float c)
{
  list<float> li({});
  float discr = b*b - 4*a*c;
  float s1=((-b+pow(discr, float(1/2)))/(2*a));
  float s2=((-b-pow(discr, float(1/2)))/(2*a));

  if(nbRacines(a, b, c) == 0)
  {li = cons(s1, li);}
  if(nbRacines(a, b, c) > 0)
  {li = cons(s1, li); li = cons(s2, li);}

  return li;
}

bool estPair(int n)
{
return n%2 == 0;
}

int somPair(int n)
{
	int som(0);
	for(int i = 1 ; i <= 2*n ; i++)
	{
		if(estPair(i))
		{
			som+=i;
		}
	}
	return som;
}

int somImpair(int n)
{
	int som(0);
	for(int i = 1 ; i <= 2*n ; i++)
	{
		if(!estPair(i))
		{
			som+=i;
		}
	}
	return som;
}

int somDiv(int n)
{
	int som(0);
	for(int i = 1 ; i <= n ; i++)
	{
		if(n%i==0)
		{
			som+=i;
		}
	}
	return som;
}

bool estParfait(int n)
{
	return somDiv(n) == 2*n;
}

bool existeParfait1(int a, int b)
{
	bool exist = false;
	for(int i = a ; i <= b ; i++)
	{
		if(estParfait(i))
		{
			exist = true;
		}
	}
	return exist;
}

bool existeParfait2(int a, int b)
{
	bool exist = false;
	int i = a;

	while(!estParfait(i) || i <= b)
	{
		if(estParfait(i))
		{
			exist = true;
		}
		i++;
	}
	return exist;
}

int parfaitSuiv(int n)
{
	int i = n+1;

	while(!estParfait(i))
	{
		i++;
	}
	return i;
}

int emeParfait(int n)
{
	int i = 0;
	int parfait = 0;

	while(i < n)
	{
		parfait = parfaitSuiv(parfait);
		i++;
	}
	return parfait;
}

bool sontAmis(int a, int b)
{
	return (somDiv(a) == (a + b)) && (somDiv(b) == (a + b)); 
}

bool aUnAmi(int n)
{
  	return sontAmis(somDiv(n),n);
}

list<int> liAmicaux(int n)
{
	list<int> li({});

	for(int i = n ; n > 0 ; i--)
	{
		if(aUnAmi(i))
		li = cons(i, li);
	}
  	return li;
}








