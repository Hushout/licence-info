#include "../header/PokemonAquatique.h"
#include <sstream>

PokemonAquatique::PokemonAquatique(std::string s , int n , int m)
: Pokemon(s , n) , nbNageoires(m) {}

std::string PokemonAquatique::toString() {

  std::stringstream s;
  s << this->nbNageoires << ' ' << this->vitesse;
  std::string sNageoires , sVitesse;
  s >> sNageoires >> sVitesse;

  return Pokemon::toString() + "ma vitesse est de " + sVitesse + "km/h et j'ai " + sNageoires + " nageoires";
}
