#include <stdio.h>
#include <stdlib.h>

int isIn(char c, char array[], int size);
void printArray(char array[], int size);

int main(int argc, char** argv){

  if(argc == 2){
    FILE* f = fopen(argv[1], "r");
    if(!f){
      printf("Erreur ouverture de fichier impossible !");
    }
    else{
      
      int nbCarDiff = 0;
      char listCarDiff[256];
      int c = 0;
      
      while((c = fgetc(f)) != EOF){
       
       if(!isIn(c, listCarDiff, nbCarDiff)){
         listCarDiff[nbCarDiff] = c;
         nbCarDiff++;
       }
     }
     printf("%d caractères differents : ", nbCarDiff);
     printArray(listCarDiff, nbCarDiff);
   }
   fclose(f);
 }
 else{
  printf("Erreur argument: %s <fichier>", argv[1]);
}
return 0;
}

int isIn(char c, char array[], int size){

  for(int i = 0 ; i < size ; i++){
    if(c == array[i]){
      return 1;
    }
  }
  return 0;
}

void printArray(char array[], int size){
  for(int i = 0 ; i < size ; i++){
    printf("%c, ", array[i]); 
  }
  printf("\b\b  \n");
}
