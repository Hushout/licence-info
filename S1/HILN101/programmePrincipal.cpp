// Fichier dans lequel vous écrirez les expressions à évaluer
#include "definitionsFonctions.cpp"
#define EVAL(exp) cout << "Valeur de " << (#exp) <<" : "<< (exp) << endl


int main()
{

  srand(time(NULL));
  boolalpha(cout);

  EVAL(triangleEqui(2,2,2));
  EVAL(triangle(2,3,1));
  EVAL(triangleRectangle(2,2,0));
  EVAL(triangleIso(2,3,1));
  EVAL(ouExcl(true, false));
  EVAL(estPair(-26));
  EVAL(existeMul11(2, 10));
  EVAL(mystere(23));
  EVAL(sompair(5));
  EVAL(somimpair(5));
  EVAL(somimpair(2));
  EVAL(somdiv(6));
  EVAL(estparfait(6));
  EVAL(estparfait(3));
  EVAL(existeparfait(3, 5));
  EVAL(parfaitsuivant(29));
  EVAL(emeparfait(3));
}

