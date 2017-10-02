#ifndef POKEMON
  #define  POKEMON
  #include "Pokemon.h"
#endif

#include <string>

class PokemonAquatique : public Pokemon{

  protected :
    const int nbNageoires;
    float vitesse;

  public :
    PokemonAquatique(std::string , int , int);
    virtual std::string toString();
};
