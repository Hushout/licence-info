#include <stdio.h>
#include <stdlib.h>

typedef struct carOcc{
  char c;
  int occ;
}carOcc;

void printCarOcc(carOcc c){
  printf("%c:%d", c.c, c.occ);
}

int isIn(char c, carOcc array[], int size);
void addOcc(char c, carOcc array[], int size);
void printArrayCarOcc(carOcc array[], int size);

int main(int argc, char** argv){

  if(argc == 2){
    FILE* f = fopen(argv[1], "r");
    if(!f){
      printf("Erreur ouverture de fichier impossible !");
    }
    else{
      
      int nbCarDiff = 0;
      carOcc listCarOcc[256];
      int c = 0;
      
      while((c = fgetc(f)) != EOF){
	
	if(!isIn(c, listCarOcc, nbCarDiff)){
	  carOcc co;
	  co.c = c;
	  co.occ = 1;
	  listCarOcc[nbCarDiff] = co;
	  nbCarDiff++;
	}
	else{
	  addOcc(c, listCarOcc, nbCarDiff);
	}
      }
      printArrayCarOcc(listCarOcc, nbCarDiff);
    }
    fclose(f);
  }
  else{
    printf("Erreur argument: %s <fichier>", argv[1]);
  }
  return 0;
}

int isIn(char c, carOcc array[], int size){

  for(int i = 0 ; i < size ; i++){
    if(c == array[i].c){
      return 1;
    }
  }
  return 0;
}

void addOcc(char c, carOcc array[], int size){
  for(int i = 0 ; i < size ; i++){
    if(c == array[i].c){
      array[i].occ++;
      break;
    }
  }
}

void printArrayCarOcc(carOcc array[], int size){
  for(int i = 0 ; i < size ; i++){
    printCarOcc(array[i]);
    printf(" ");
  }
  printf("\n");
}
