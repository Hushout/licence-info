#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
typedef struct coord{int abs; int ord;} coord;

void pointrandom(int n, coord point[]);
void printpoint(int n, coord point[]);

void distances(int n, int m, coord point[], int edge[][3]);
void printedge(int m, int edge[][3]);

void swap(int& a, int& b);
void tribulle(int m, int edge[][3]);

void kruskal(int n, int edge[][3], int arbre[][2]);
void printarbre(int n, int arbre[][2]);

int pivot(int edge[][3], int deb, int fin);
void trirapidebis(int edge[][3], int deb, int fin);
void trirapide(int taille, int edge[][3]);

int main(int argc, char** argv)
{
  if(argc == 2){
    srand(time(NULL));
    int n = atoi(argv[1]);             //Le nombre de points.
    //cout << "Entrer le nombre de points: ";
    //cin >> n;
    int m=n*(n-1)/2;   // Le nombre de paires de points.
    coord point[n];    // Les coordonnees des points dans le plan.
    int edge[m][3];    // Les paires de points et le carre de leur longueur.
    int arbre[n-1][2]; // Les aretes de l'arbre de Kruskal.

    pointrandom(n, point);
    printpoint(n, point);
    cout << endl;
    distances(n, m, point, edge);
    printedge(m, edge);
    cout << endl;
    cout << "tri:" << endl;
    trirapide(m, edge);
    printedge(m, edge);
    cout << endl;
    cout << "arbre:" << endl;
    kruskal(n, edge, arbre);
    printarbre(n-1, arbre);
  }
  else{
    cout << "Erreur d'argument: " << argv[0] << " <nbsommets>" << endl;
  }
  return EXIT_SUCCESS;
}

void pointrandom(int n, coord point[]){
  
    for(int i = 0 ; i < n  ; i++){
      point[i].abs = rand() % 613;
      point[i].ord = rand() % 793;
    }
}

void printpoint(int n, coord point[]){
  cout << "{";
  for(int i = 0 ; i < n ; i++){
    cout << "{" << point[i].abs << ", " << point[i].ord << "} ";
  }
  cout << "\b}\n";
}

void distances(int n, int m, coord point[], int edge[][3]){

    int k = 0;
    
    for(int i = 0 ; i < n - 1 ; i++) {
        
        for(int j = i + 1 ; j < n ; j++) {
            edge[k][0] = i;
            edge[k][1] = j;
            edge[k][2] = pow(point[j].abs - point[i].abs , 2) + pow(point[j].ord - point[i].ord , 2);
            k++;
        }
    }
}

void printedge(int m, int edge[][3]){
  cout << "{";
  for(int i = 0 ; i < m ; i++){
    cout << "{" << edge[i][0] << ", " <<  edge[i][1] << ", " << edge[i][2] << "} ";
  }
  cout << "\b}\n";
}

void swap(int& a, int& b){
  int temp = a;
  a = b;
  b = temp;
}

void tribulle(int m, int edge[][3]){
      
  bool trie = false;

  while(!trie){
    
    trie = true;
    
    for(int i = 0 ; i < m-1  ; i++){
      if(edge[i+1][2] < edge[i][2]){
	swap(edge[i+1][0], edge[i][0]);
	swap(edge[i+1][1], edge[i][1]);
	swap(edge[i+1][2], edge[i][2]);
	trie = false;
      }
    }
  }
}

void kruskal(int n, int edge[][3], int arbre[][2]){
  
  int comp[n];
  int h = 0;
    
  for(int i = 0 ; i < n ; i++) {
    comp[i] = i;
  }
    
  for(int i = 0 ; i < n ; i++) {
        
    if(comp[edge[i][0]] != comp[edge[i][1]]) {
      
      int aux = comp[edge[i][0]];
      arbre[h][0] = edge[i][0];
      arbre[h][1] = edge[i][1];
      h++;
            
      for(int k = 0 ; k < n ; k++) {
                
	if(comp[k] == aux) {
	  comp[k] = comp[edge[i][1]];
	}
      }
    }
  }
}

void printarbre(int n, int arbre[][2]){
    cout << "{";
  for(int i = 0 ; i < n ; i++){
    cout << "{" << arbre[i][0] << ", " <<  arbre[i][1] << "} ";
  }
  cout << "\b}\n";
}


int pivot(int edge[][3], int deb, int fin){
  int p = deb;
  int pivotElement = edge[deb][2];
 
  for(int i = deb+1 ; i <= fin ; i++){

    if(edge[i][2] <= pivotElement){
      p++;
      swap(edge[i][0], edge[p][0]);
      swap(edge[i][1], edge[p][1]);
      swap(edge[i][2], edge[p][2]);
    }
  }
  swap(edge[p][0], edge[deb][0]);
  swap(edge[p][1], edge[deb][1]);
  swap(edge[p][2], edge[deb][2]); 
  return p;
}

void trirapidebis(int edge[][3], int deb, int fin){
    int pivotElement;
 
    if(deb < fin)
    {
        pivotElement = pivot(edge, deb, fin);
        trirapidebis(edge, deb, pivotElement-1);
        trirapidebis(edge, pivotElement+1, fin);
    }
}

void trirapide(int taille, int edge[][3]){
  trirapidebis(edge, 0, taille-1);
}
