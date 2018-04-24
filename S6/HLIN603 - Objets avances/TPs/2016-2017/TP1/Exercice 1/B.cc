#include "B.h"
#include <sstream>

B::B(int i, int j) : A(i){
 this->j = j;
}

std::string B::quiEsTu() {
  return "Je suis un B";
}

std::string B::toString() {
  std::stringstream sstream;
  sstream << this->j;
  std::string js;
  sstream >> js;
  return A::toString() + "\n j = " + js;
}
