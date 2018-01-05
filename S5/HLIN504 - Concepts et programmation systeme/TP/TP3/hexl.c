#include <stdio.h>
#include <stdlib.h>

void printhex(int nbc, char array[], int size);

int main(int argc, char** argv){

  if(argc == 2){
    FILE* f = fopen(argv[1], "r");
    if(!f){
      printf("Erreur ouverture de fichier impossible !");
    }
    else{

      char ligne[16];
      ligne[16] = '\0';
      int numc = 0;
      int nbc = 0;
      int c = 0;
      
      while((c = fgetc(f)) != EOF){

	if(c == '\n'){c='.';}
	ligne[numc] = c;
	numc++;
	
	if(numc % 16 == 0 && numc != 0){
	  printhex(nbc, ligne, 16);
	  printf(" %s\n", ligne);
	  numc = 0;
	}
	nbc++;
      }
      printf("\n");
    }
    fclose(f);
  }
  else{
    printf("Erreur argument: %s <fichier>", argv[1]);
  }
  return 0;
}


void printhex(int nbc, char array[], int size){
  int n = 0;
  printf("%08x: ", nbc);
  for(int i = 0 ; i < size ; i++){
    if(n % 2 == 0 && n != 0){
      printf(" ");
      n = 0;
    }
    n++;
    printf("%2x", array[i]);
  }
}
