// Fichier dans lequel vous écrirez les expressions à évaluer
#include "definitionsFonctions.cpp"
#define EVAL(exp) cout << "Valeur de " << (#exp) <<" : "<< (exp) << endl


int main()
{
   srand(time(NULL));
   boolalpha(cout);

EVAL(estPair(-2));

EVAL(existeMul11(2,10));
EVAL(existeMul11(22,22));
EVAL(existeMul11(22,2));

EVAL(maxMul11(3,43));
EVAL(maxMul11(3,4));

EVAL(nbMul11(3,43));
EVAL(nbMul11(3,4));

EVAL(somMul11(3,54));
EVAL(nbMul11(3,4));

EVAL(nbChifDec(3279));

EVAL(chifRang(3249, 3));

EVAL(somChif(3249));

EVAL(racNum(3249));

EVAL(invChif(3249));

EVAL(existeRac(9, 2));

EVAL(estCarre(5));
EVAL(estCarre(9));

  return 0;
}

