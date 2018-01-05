#include <iostream>
#include "abr.h"

int main(int argc, char** argv){

  ABR<int> A1, A3;
  A1.insert(4);
  A1.insert(5);
  A1.insert(2);
  A3 = A1;
  A3.affiche();
  
  return 0;
}
