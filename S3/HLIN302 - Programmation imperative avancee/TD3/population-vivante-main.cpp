#include "population-vivante.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main(int argc , char* argv[]){

  if(argc < 4){
    std::cout << "Erreur arg : ./population-vivante taillePop nbAlive nbTour vitItMs " << std::endl;
  }

  else{

    PopulationVivante JDV(atoi(argv[1]));
    JDV.init(atoi(argv[2]));
    
    system("clear");
    JDV.print();
    int k = atoi(argv[3]);
    
    usleep(atoi(argv[4]));

    
      while(JDV.nb_vivants() > 0 &&  k > 0){
      system("clear");
      JDV=JDV.next();
      JDV.print();
      usleep(atoi(argv[4]));
      k++;
    }
  }
  
  return 0;
}
