#ifndef POKEMON_TERRESTRE
  #define  POKEMON_TERRESTRE
  #include "PokemonTerrestre.h"
#endif

class PokemonCasanier : public virtual PokemonTerrestre {
  
  private :
    const int heuresDevantLaTeleParJour;

  public :
    PokemonCasanier(std::string , int , int , float , int);
    std::string toString();
};
