#include <iostream>
#include <cstdlib>
#include <ctime>


/************************
Generaux
****************************/
int max(int a, int b) {if (a > b) return a; return b;}

int moitieSuperieure(int n){
  if (n % 2 == 0) return n / 2; return (n+1) / 2;}

void imprimer(int n, int T[]){
  for (int i=0; i<n; i++) std::cout<<T[i]<<" ";}

void genererInverse(int n, int T[]){
  for  (int i=0; i<n; i++) T[i]=n-i;
}


void genererRandom(int n, int Max, int T[]){//rempli le tableau T de n nombres aléatoires, tous enttre 0 et Max
  for  (int i=0; i<n; i++) T[i]=rand() % (Max + 1);
}


void echanger(int T[], int i, int j){
  int temp=T[i]; T[i]=T[j]; T[j]=temp;
}

////////////////////////////////////////////////////
/////////////////EXERCICE DE TRIE///////////////////
////////////////////////////////////////////////////

void afficheT(int T[], int taille){
  for(int i = 0 ; i < taille ; i++){
    std::cout << T[i] << " ";
  }
}


//copy: renvoie une copy du tableau mis en paramètre

int* copy(int T[], int taille){
  int* T2 = new int[taille];
  for(int i = 0 ; i < taille ; i++){
    T2[i] = T[i];
  }
  return T2;
}

void triPanier(int T[], int taille, int max){
  
  int k = 0;
  int* Panier = new int[max+1];

  //Initialisation du Panier
  
  for(int i = 0 ; i < max+1 ; i++){
    Panier[i] = 0;
  }
  
  //Comptage du nombre de valeurs dans le Panier
  
  for(int i = 0 ; i < taille ; i++){
    Panier[T[i]]++ ;
  }
  
  //Tri grace au panier
  
  for(int i = 0 ; i < max+1 ; i++){

    while(Panier[i] > 0){
      T[k] = i;
      Panier[i]--;
      k++;
    }
  }
}

int pivot(int T[], int deb, int fin){
  int p = deb;
  int pivotElement = T[deb];
 
  for(int i = deb+1 ; i <= fin ; i++){

    if(T[i] <= pivotElement){
      p++;
      echanger(T, i, p);
    }
  }
 
  echanger(T, p, deb);
 
  return p;
}

void triRapideBis(int T[], int deb, int fin){
    int pivotElement;
 
    if(deb < fin)
    {
        pivotElement = pivot(T, deb, fin);
        triRapideBis(T, deb, pivotElement-1);
        triRapideBis(T, pivotElement+1, fin);
    }
}

void triRapide(int T[], int taille){
  triRapideBis(T, 0, taille-1);
}

void triBulle(int T[], int taille){
      
  bool trie = false;

  while(!trie){
    
    trie = true;
    
    for(int i = 0 ; i < taille-1  ; i++){
      if(T[i+1] < T[i]){
	echanger(T, i, i+1);
	trie = false;
      }
    }
  }
}

int main(int argc, char** argv){

  int taille = 10;
  int max = 10;
  
  if(argc == 2){
    //Change la taille du tableau selon l'argument argv.
    taille = atoi(argv[1]);
    max = taille;
  }
  
  //Initialisation du Tableau

  clock_t time;

  int* T = new int[taille];
  int* Temp;
    
  genererRandom(taille, max, T);
  
  Temp = copy(T, taille); //Temp contiendra le tableau non triée.
    
  std::cout << "T = ";
  afficheT(T, taille);
  std::cout << std::endl << std::endl;
  
  //TRI PANIER
    
  time = clock();
  triPanier(T, taille, max);
  time = clock() - time;
    
  std::cout << "TriPanier(T): ";
  afficheT(T, taille);
  std::cout << std::endl;
  std::cout << "Temps d'exec: "
	    << ((float)time)/CLOCKS_PER_SEC << "s" << std::endl << std::endl;


  //TRI RAPIDE
    
  T = copy(Temp, taille); //T prend les valeurs du tableau non triée
  time = clock();
  triRapide(T, taille);
  time = clock() - time;
    
  std::cout << "TriRapide(T): ";
  afficheT(T, taille);
  std::cout << std::endl;
  std::cout << "Temps d'exec: "
	    << ((float)time)/CLOCKS_PER_SEC << "s" << std::endl << std::endl;

    
  //TRI BULLE

  T = copy(Temp, taille); //T prend les valeurs du tableau non triée
    
  time = clock();
  triBulle(T, taille); 
  time = clock() - time;
    
  std::cout << "TriBulles(T): ";
  afficheT(T, taille);
  std::cout << std::endl;
  std::cout << "Temps d'exec: "
	    << ((float)time)/CLOCKS_PER_SEC << "s" << std::endl << std::endl;
  
  std::cout << "Options d'executions: " << argv[0] << " <taille> = 10 par defaut"<< std::endl;
}


/*
Ex3:

a) Pour le trie à bulle de complexité O(n²):

à partir d'une taille de tableau de 100 000 
la differente de complexité ce fait bien ressentir

Sont temps d'execution est de ~40s alors que 
celui des autres est casi instantané.

b) Pour le trie rapide de complexité O(nlog(n)):

à partir d'une taille de tableau de 10 000 000 
la differente de complexité ce fait bien ressentir

Sont temps d'execution est de ~3s alors que 
celui des du tri panier est casi instantané.

*/

//g++ -o tri TriOutilsSimples.cpp
