#include <iostream>
#include <cmath>
#include <cstdlib>     /* atoi */

//Odorico Thibault L2 groupe B

#include "fonctionsMysterieuses.h"

int apuissanceb(int a, int b) {
// renvoie a puissance b
  if (b==0) return 1;
  if (b % 2 == 0) return apuissanceb(a * a, b / 2);
  return a * apuissanceb(a,b-1);}

int incrementer(int n, bool T[]){
  
}

int main(int argv, char** argc){

  int numeroFonction = atoi(argc[1]),
     n =  atoi(argc[2]),
    v;
  
  //Modification ici ! les solutions s'affiche à l'execution du programme
  switch (numeroFonction) {
  case 1 : v=f1(n); std::cout << "racine(n)*3 = "; break;
  case 2 : v=f2(n); std::cout << "puiss5(n)*0.1 = "; break;
  case 3 : v=f3(n); std::cout << "puiss2(n)*0.5 = "; break;
  case 4 : v=f4(n); std::cout << "log(n)*2 = ";break;
  case 5 : v=f5(n); std::cout << "2 exp(n)*10 = "; break;
  case 6 : v=f6(n); std::cout << "3 exp(n)*20 = "; break;
  }

  std::cout<<"f"<<numeroFonction<<"("<<n<<") renvoie "<<v<<"\n";
  return 0;
}

/*
ordre de compilation :  g++ SolutionsFonctionMysterieuses.cpp fonctionsMysterieuses.o -o test
Ordre d'exécution :  ./test 1 2 
*/

