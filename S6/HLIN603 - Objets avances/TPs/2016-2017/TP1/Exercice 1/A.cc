#include "A.h"
#include <sstream>

A::A(int i) {
  this->i = i;
}

std::string A::quiEsTu() {
  return "Je suis un A";
}

std::string A::toString() {
  std::stringstream sstream;
  sstream << this->i;
  std::string is;
  sstream >> is;
  return "i = " + is;
}

std::string A::presenteToi() {
  return this->quiEsTu() + this->toString();
}
