#include "../header/PokemonSportif.h"
#include <sstream>

PokemonSportif::PokemonSportif(std::string s , int n , int m , float t , int b)
: PokemonTerrestre(s , n , m , t) , battementsParMinute(b) {}

std::string PokemonSportif::toString() {

  std::stringstream s;
  std::string sBattementsParMinute;
  s << this->battementsParMinute;
  s >> sBattementsParMinute;

  return PokemonTerrestre::toString() + " et ma fréquence cardiaque est de " + sBattementsParMinute + " battements par minute";
}
