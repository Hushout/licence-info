#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  printf("Nombre d'arguments: %d\n", argc);
  printf("Les arguments: ");
  for(int i = 0 ; i < argc ; i++){
    printf("%s ", argv[i]);
  }
  printf("\n");
  return 0;
}
