#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  if(argc == 3){
    FILE* f = fopen(argv[1], "r");
    if(!f){
      fprintf(stderr, "Erreur ouverture de fichier impossible !");
    }
    else{

      char cible = argv[2][0];
      char c = 0;
      fseek(f, 0, SEEK_END);
      int fin = ftell(f);
      int deb = 0;
      fseek(f, 0, deb);
      
      while((c = fgetc(f)) != EOF){
	
	if(c == cible || fin <= deb){
	  break;
	}
	else if(c < cible){
	  deb = (deb + fin)/2;
	  fseek(f, 0, deb);
	}
	else{
	  fin = (deb + fin)/2;
	  fseek(f, 0, fin);
	}
      }
      if(fin > deb){
	int position = ftell(f)-1;
	printf("Le caractères %c est en position %d\n", cible, position);
      }
      else{
	printf("Le caractères n'est pas dans le fichier\n");
      }
    }
    fclose(f);
  }
  else{
    printf("Erreur argument: %s <fichier> <caractère>", argv[0]);
  }
  return 0;
}
