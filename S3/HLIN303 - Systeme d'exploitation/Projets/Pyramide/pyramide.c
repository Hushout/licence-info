#include <stdio.h>
#include <stdlib.h>

int tailleNb(int n){
  return n/10 == 0 ? 1 : tailleNb(n/10) + 1;
}

int puiss(int a, int b){
  int res = 1;
  for(int i = 0 ; i < b ; i++){
    res = res*a;
  }
  return res;
}

int estPuiss(int n, int a){  //test si n est une puiss de a
  float res = n;
  while(res > a){
    res/=a;
  }
  return n == 1 ? 1 : res == a;
}

void espacer(int n){
  for(int i = 0 ; i < n ; i++){
    printf(" ");
  }
}

void afficheVal(int* tabVal, int nbVal, int espAv, int espInterVal, int espApresVal){

  int k = 0;
  espacer(espAv);
  
  for(int i = 0 ; i < nbVal ; i++){
    
    printf("%d", tabVal[k]);
    espacer(espInterVal - (tailleNb(tabVal[k])-1));
    printf("%d", tabVal[k+1]);
    espacer(espApresVal - (tailleNb(tabVal[k+1])-1));
    k+=2;
  }
  printf("\n");
}

void affichelignePyr(int nbPyr, int espAv, int espInterCotes, int espApresPyr){

  espacer(espAv);
  
  for(int i = 0 ; i < nbPyr ; i++){
    
    printf("/");
    espacer(espInterCotes);
    printf("\\");
    espacer(espApresPyr);
  }
  printf("\n");
}

void affichePyr(int* tabVal, int nbPyr, int hauteur, int espAv, int espInterCotes, int espInterPyr){

  int h = hauteur-1;
  int augInterCotes = 0;
  int redInterPyr = hauteur*2 - 2;
  
  for(int i = 0 ; i < hauteur ; i++){
    
    if(i < hauteur - 1){
      affichelignePyr(nbPyr, espAv+h, espInterCotes+augInterCotes, espInterPyr + redInterPyr);
    }
    else{
      afficheVal(tabVal,nbPyr, espAv+h, espInterCotes+augInterCotes, espInterPyr + redInterPyr);
    }
    augInterCotes+=2;
    redInterPyr-=2;
    h--;
  }
}

void afficheArbreBin(int* tabVal, int profondeur){

  int hauteur = puiss(2, profondeur);
  int k = 0, espInterPyr = 0, espApresPyr = hauteur*2;
  
  for(int i = profondeur ; i > 0 ; i--){
    affichePyr(tabVal + puiss(2, k+1)-1, puiss(2, k), hauteur, hauteur-2, espInterPyr, espApresPyr);
    hauteur/=2;
    espApresPyr/=2;
    k+=1;
  }
}

int main(int argc, char** argv){

  if(argc != 2){
    printf("ERREUR : %s taille\n", argv[0]);
    return 1;
  }
  
  const int t = 200;
    int tabVal[t];
    
    for(int i = 0 ; i < t ; i++){
      tabVal[i] = i;
    }

  afficheArbreBin(tabVal, atoi(argv[1]));
  return 0;
}
