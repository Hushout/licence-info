#include "../header/PokemonMer.h"

PokemonMer::PokemonMer(std::string s , int n , int m) : PokemonAquatique(s , n , m) {
  this->vitesse = (float)(this->poids / 25 * this->nbNageoires);
}
