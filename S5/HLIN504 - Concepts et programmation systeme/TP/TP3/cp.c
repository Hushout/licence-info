#include <stdio.h>
#include <stdlib.h>

void printhex(int nbc, char array[], int size);

int main(int argc, char** argv){

  if(argc == 3){
    FILE* source = fopen(argv[1], "r");
    if(!source){
      fprintf(stderr, "Erreur ouverture de fichier impossible !");
    }
    else{

      FILE* dest = fopen(argv[2], "w");

      if(dest){
	 fprintf(stderr, "Attention overwrite !");
      }
      
      char c = 0;
      
      while((c = fgetc(source)) != EOF){
	fputc(c, dest);
      }
      fclose(dest);
    }
    fclose(source);
  }
  else{
    printf("Erreur argument: %s <source> <dest>", argv[0]);
  }
  return 0;
}

