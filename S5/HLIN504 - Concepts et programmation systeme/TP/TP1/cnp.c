#include <stdlib.h>
#include <stdio.h>

struct TriangleP {
  int size;
  int* data;
};

typedef struct TriangleP TriangleP;

/*alloue un triangle de taille size sans initialiser ses valeurs*/
TriangleP* allocateTriangle(int size);

/*desalloue le triangle*/
void deleteTriangle(TriangleP* t);

/*crée un triangle avec pour seule valeur 1*/
TriangleP* createTriangle();

/*affiche le triangle t*/
void printTriangle(TriangleP* t);

/*renvoie le triangle suivant formé a partir de prec*/
TriangleP* nextTriangle(const TriangleP* prec);

int main(int argc, char* argv[]){

  if(argc == 2){
    if(atoi(argv[1]) > 0){
      TriangleP* t = createTriangle();
      printTriangle(t);

      for(int i = 1 ; i < atoi(argv[1]) ; i++){
	t = nextTriangle(t);
	printTriangle(t);
      }
    }
  }
  else{
    printf("Erreur: mauvais argument %s n p\n", argv[0]);
  }
  return 0;
}

TriangleP* allocateTriangle(int size){
  TriangleP* newT = malloc(sizeof(TriangleP));
  newT->size = size;
  newT->data = malloc(sizeof(int) * size);
  return newT;
}

void deleteTriangle(TriangleP* t){
  free(t->data);
  free(t);
}

TriangleP* createTriangle(){
  TriangleP* newT = allocateTriangle(1);
  newT->data[0] = 1;
  return newT;
}

void printTriangle(TriangleP* t){
  for(int i = 0 ; i < t->size ; i++){
    if(i == t->size - 1)
      printf("%d\n", t->data[i]);
    else
      printf("%d ", t->data[i]);
  }
}

TriangleP* nextTriangle(const TriangleP* t){

  TriangleP* nextT = allocateTriangle(t->size + 1);
  
  for(int i = 0 ; i < t->size ; i++){
    if(i == 0)
      nextT->data[i] = 1;
    else
      nextT->data[i] = t->data[i] + t->data[i - 1];
  }
  nextT->data[t->size] = 1;
  
  return nextT;
}
