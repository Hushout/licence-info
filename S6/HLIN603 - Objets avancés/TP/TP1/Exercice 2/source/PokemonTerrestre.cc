#include "../header/PokemonTerrestre.h"
#include <sstream>

PokemonTerrestre::PokemonTerrestre(std::string s , int n , int m , float t)
: Pokemon(s , n) , nbPattes(m) , taille(t) , vitesse(t * m * 3){}

std::string PokemonTerrestre::toString() {

  std::stringstream s;
  s << this->nbPattes << ' ' << this->vitesse << ' ' << this->taille;
  std::string sPattes , sVitesse, sTaille;
  s >> sPattes >> sVitesse >> sTaille;

  return Pokemon::toString() + "ma vitesse est de " + sVitesse + "km/h, j'ai " + sPattes + " pattes, ma taille est de " + sTaille +"m, ";
}
