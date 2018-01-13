#include "../header/PokemonCroisiere.h"

PokemonCroisiere::PokemonCroisiere(std::string s , int n , int m) : PokemonAquatique(s , n , m) {
  this->vitesse = (float)((this->poids / 25 * this->nbNageoires) / 2);
}
