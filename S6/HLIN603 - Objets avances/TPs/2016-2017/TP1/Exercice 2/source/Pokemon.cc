#include "../header/Pokemon.h"
#include <sstream>
#include <iostream>

Pokemon::Pokemon(std::string s, int n) : nom(s) , poids(n) {}

std::string Pokemon::toString() {

  std::stringstream ss;
  std::string poids;
  ss << this->poids;
  ss >> poids;

  return "Je suis le Pokemon " + this->nom + ", mon poids est de " + poids + "kg, ";
}
