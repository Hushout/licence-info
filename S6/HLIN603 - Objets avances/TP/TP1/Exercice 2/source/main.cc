#include <iostream>
#include <string>
#include "../header/PokemonSportif.h"
#include "../header/PokemonCasanier.h"
#include "../header/PokemonMer.h"
#include "../header/PokemonCroisiere.h"

int main(int argc , char * argv[]) {

  PokemonSportif    A ("Machopeur" , 100 , 4 , 1.95 , 213);
  PokemonCasanier   B ("Rondoudou" , 35 , 4 , 0.80 , 8);
  PokemonMer        C ("Groudon" , 3000 , 8);
  PokemonCroisiere  D ("Tortank" , 1200 , 0);

  std::cout << A.toString() << std::endl
            << B.toString() << std::endl
            << C.toString() << std::endl
            << D.toString() << std::endl;

  return 0;
}
