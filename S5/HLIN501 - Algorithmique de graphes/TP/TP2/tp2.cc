#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Affichage.h"

using namespace std;
//typedef struct coord{int abs; int ord;} coord;

void pointrandom(int n, coord point[]);
void printpoint(int n, coord point[]);

void distances(int n, coord point[], int edge[][3]);
void printedge(int m, int edge[][3]);

void swap(int& a, int& b);
void tribulle(int m, int edge[][3]);

void kruskal(int n, int edge[][3], int arbre[][2]);
void printarbre(int n, int arbre[][2]);

int pivot(int edge[][3], int deb, int fin);
void trirapidebis(int edge[][3], int deb, int fin);
void trirapide(int taille, int edge[][3]);

int main(int argc, char* argv[])
{
  if(argc >= 2/*&& argc <= 3*/){
	  
    srand(time(NULL));
    int n = atoi(argv[1]);             //Le nombre de points.
    int m=n*(n-1)/2;   // Le nombre de paires de points.
    coord* point = new coord[n];    // Les coordonnees des points dans le plan.
	int (*edge)[3] = new int[m][3];    // Les paires de points et le carre de leur longueur.
    int (*arbre)[2] = new int[n-1][2]; // Les aretes de l'arbre de Kruskal.

	cout << "-Randomizing point..." << endl;	
    pointrandom(n, point);
    if(argc == 3 /* && argv[2] == "-p"*/){
		printpoint(n, point);
	}
	cout << "done" << endl;

	cout << "-Creating edge..." << endl;		
    distances(n, point, edge);
	
    if(argc == 3  /* argv[2] == "-p"*/){
		printedge(m, edge);
	}
	cout << "done" << endl;

    cout << "-Sorting edge..." << endl;
    trirapide(m, edge);
	
    if(argc == 3  /* argv[2] == "-p"*/){
		printedge(m, edge);
	}
	cout << "done" << endl;
	
    cout << "-Creating arbre..." << endl;
    kruskal(n, edge, arbre);
	
	if(argc == 3  /* argv[2] == "-p"*/){
		printarbre(n-1, arbre);
	}
	cout << "done" << endl;
	
	cout << "-Outputing arbre in Exemple.pdf..." << endl;
	AffichageGraphique(n, point, arbre); //output => Exemple.ps
	system("ps2pdf Exemple.ps"); //create .pdf with the .ps file
	cout << "done" << endl;	
	
	delete[] point;
	delete[] edge;
	delete[] arbre;
  }
  else{
    cout << "Erreur d'argument: " << argv[0] << " <nbsommets> <option> (-p => affiche structure terminal)" << endl;
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

void distances(int n, coord point[], int edge[][3]){

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
  int* comp = new int[n];
  int m = n*(n-1)/2;
  int aux1 = 0, aux2 = 0, h = 0;
  vector<vector<int> > listComp;
  
  for(int i = 0 ; i < n ; i++){
    comp[i] = i;
    vector<int> vect;
    vect.push_back(i);
    listComp.push_back(vect);
  }
  
  for(int j = 0; j < m; j++){
    
    if(comp[edge[j][0]] != comp[edge[j][1]]){
      aux1 = comp[edge[j][0]];
      aux2 = comp[edge[j][1]];
      
	  arbre[h][0] = edge[j][0];
	  arbre[h][1] = edge[j][1];
	  h++;
	  
      if(listComp[aux1].size() > listComp[aux2].size()){
		swap(aux1, aux2);
      }
      while(!(listComp[aux1].empty())){
		int d = listComp[aux1].back();
		listComp[aux2].push_back(d);
		comp[d]=aux2;
		listComp[aux1].pop_back();
      }
    }
  }
  delete[] comp;
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
