// Fichier dans lequel vous écrirez les expressions à évaluer
#include "definitionsFonctions.cpp"
#define EVAL(exp) cout << "Valeur de " << (#exp) <<" : "<< (exp) << endl


int main()
{
   srand(time(NULL));
   boolalpha(cout);
EVAL(mystere(23));
EVAL(mystere(39));
EVAL(nbRacines(0.3, 1, -35));
EVAL(solsDegrees2(0.3, 1, -35));
EVAL(somPair(5));
EVAL(somImpair(5));
EVAL(somImpair(2));
EVAL(somImpair(3));
EVAL(somImpair(4));
EVAL(somDiv(6));
EVAL(estParfait(28));
EVAL(estParfait(66));
EVAL(existeParfait1(1,30));
EVAL(existeParfait1(1,5));
EVAL(existeParfait1(1,6));
EVAL(existeParfait2(1,30));
EVAL(existeParfait2(1,5));
EVAL(existeParfait2(1,6));
EVAL(parfaitSuiv(7));
EVAL(emeParfait(3));
EVAL(sontAmis(220, 284));
EVAL(aUnAmi(220));
return 0;
}

