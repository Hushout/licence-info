#ifndef POKEMON
  #define  POKEMON
  #include "Pokemon.h"
#endif

#include <string>

class PokemonTerrestre : public Pokemon{
  
  protected :
    const int nbPattes;
    const float taille , vitesse;

  public :
    PokemonTerrestre(std::string , int , int , float);
    virtual std::string toString();
};
