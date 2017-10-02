#include <iostream>
#include <string>

class Pokemon {

  protected :
    const std::string nom;
    const int poids;

  public :
    Pokemon(std::string , int);
    virtual std::string toString();
};
