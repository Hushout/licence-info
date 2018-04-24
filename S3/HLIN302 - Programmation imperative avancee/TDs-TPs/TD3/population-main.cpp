#include "population.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main(int argc , char* argv[]){

  if(argc < 3){
    std::cout << "Erreur arg : ./population nbAlive nbTour vitItMs " << std::endl;
  }

  else{

    Population JDV;
    JDV.init(atoi(argv[1]));
    
    system("clear");
    JDV.print();
    int k = atoi(argv[2]);
    
    usleep(atoi(argv[3]));

    
      while(JDV.nb_vivants() > 0 &&  k > 0){
      system("clear");
      JDV=JDV.next();
      JDV.print();
      usleep(atoi(argv[3]));
      k++;
    }
  }
  
  return 0;
}
