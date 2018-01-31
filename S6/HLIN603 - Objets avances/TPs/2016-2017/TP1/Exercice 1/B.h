#include "A.h"
#include <iostream>

class B : public A{
  private :
  int j;

  public :
  B(int , int);
  std::string quiEsTu();
  std::string toString();
};
