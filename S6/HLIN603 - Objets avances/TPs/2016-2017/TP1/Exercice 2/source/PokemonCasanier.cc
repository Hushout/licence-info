#include "../header/PokemonCasanier.h"
#include <sstream>

PokemonCasanier::PokemonCasanier(std::string s , int n , int m , float t , int h)
: PokemonTerrestre(s , n , m , t) , heuresDevantLaTeleParJour(h) {}

std::string PokemonCasanier::toString() {

  std::stringstream s;
  std::string sHeuresDevantLaTeleParJour;
  s << this->heuresDevantLaTeleParJour;
  s >> sHeuresDevantLaTeleParJour;

  return PokemonTerrestre::toString() + " et je passe " + sHeuresDevantLaTeleParJour + " heures devant la tele chaque jour";
}
