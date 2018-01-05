#ifndef POKEMON_TERRESTRE
  #define  POKEMON_TERRESTRE
  #include "PokemonTerrestre.h"
#endif

class PokemonSportif : public virtual PokemonTerrestre {
  
  private :
    const int battementsParMinute;

  public :
    PokemonSportif(std::string , int , int , float , int);
    std::string toString();
};
