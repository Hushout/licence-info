#include <stdio.h>
#include <stdlib.h>

//char **env = environ; (sur système posix)

//getenv(char* string); return la valeur de la variable environnement
//setenv(const char* name, const char* value, int overwrite); modifie ou ajoute une variable environnement
//unsetenv(const char* name); efface la variable name de l'environnement

int main(int argc, char* argv[], char* env[]){
  printf("Nombre d'arguments: %d\n", argc);
  printf("Les arguments: \n");
  for(int i = 0 ; i < argc ; i++){
    printf("%s \n", argv[i]);
  }
  printf("\n");
  int i = 0;
  while(env[i]){
	printf("%s \n", env[i]);
	i++;
  }
   printf("\n");
  return 0;
}
