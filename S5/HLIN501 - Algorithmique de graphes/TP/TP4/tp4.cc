
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <ctime>
#include <limits>

#include "Affichage.h"

using namespace std;

void printarray(int n, int array[]);

float distance(coord* a, coord* b); 
void pointrandom(int n, coord point[]);
void printpoint(int n, coord point[]);

void voisins(int n, int dmax, coord point[], vector<int> voisin[]);
void printvoisins(int n, vector<int> voisin[]);

void dijkstra(int n, vector<int> voisin[], coord point[], int pere[]);
int existenontraite(int traite[], int n); //renvoie l'indice du sommet non traité ou -1 si aucun
int minxnontraite(int traite[], float d[], int n, int inontraite); // i = premier sommet non traité

int main(int argc, char* argv[]){

	srand(time(NULL));
	if(argc == 3){
		int n = atoi(argv[1]);                   //Le nombre de points.

		int dmax = atoi(argv[2]);             // La distance jusqu'a laquelle on relie deux points.

		clock_t time;

		vector<int>* voisin = new vector<int>[n];   // Les listes de voisins.
		coord *point = new coord[n];         // Les coordonnees des points.

		//int (*arbre)[2] = new int[n-1][2];         // Les aretes de l'arbre de Dijkstra.
		int* pere = new int[n];             // La relation de filiation de l'arbre de Dijkstra.



		cout << "-Randomizing point..." << endl;
		time = clock();
		pointrandom(n, point);
		time = clock() - time;
		//printpoint(n, point);
		cout << "done in " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		cout << "-Generating voisin..." << endl;
		time = clock();
		voisins(n, dmax, point, voisin);
		time = clock() - time;
		//printvoisins(n, voisin);
		cout << "done in " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		cout << "-Applying dijkstra..." << endl;
		time = clock();
		dijkstra(n, voisin, point, pere);
		time = clock() - time;
		printarray(n, pere);
		cout << "done in " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		AffichageGraphiqueVoisins(n, point, voisin); //output => Voisins.ps
		AffichageGraphiqueParcours(n, point, pere); //output => Parcours.ps 
	}
	else{
		cout << "Erreur d'argument: " << argv[0] << " <sommets> <dist>" << endl;
	}
	return 0;
}

void printarray(int n, int array[]){
  cout << "{";
  for(int i = 0 ; i < n ; i++){
    cout << array[i] << ", ";
  }
  cout << "\b\b}\n";
}

float distance(coord* a, coord* b){
	return pow(pow(b->abs - a->abs , 2) + pow(b->ord - a->ord , 2), (float)1/2);
}

void pointrandom(int n, coord point[]){
	int i = 0;
	while(i < n){
		point[i].abs = rand() % 613;
		point[i].ord = rand() % 793;
		i++;
	}
}

void printpoint(int n, coord point[]){
	cout << "{";
	for(int i = 0 ; i < n ; i++){
		cout << "{" << point[i].abs << ", " << point[i].ord << "} ";
	}
	cout << "\b}\n";
}


void voisins(int n, int dmax, coord point[], vector<int> voisin[]){

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){
			if(j != i){
				float dist = distance(&point[i], &point[j]);
				if(dist <= dmax){
					voisin[i].push_back(j);
				}
			}
		}
	}
}

void printvoisins(int n, vector<int> voisin[]){
	cout << "{";
	for(int i = 0 ; i < n ; i++){
		cout << "{ ";
		for(int j = 0 ; j < (int)voisin[i].size() ; j++){
			cout << voisin[i][j] << " ";
		}
		cout << "}";
	}
	cout << "}\n";
}

void dijkstra(int n, vector<int> voisin[], coord point[], int pere[]){

  float* d = new float[n];
  int* traite = new int[n];
  
  for(int i = 0 ; i < n ; i++){
	d[i] = numeric_limits<float>::infinity();
	traite[i] = 0;
	pere[i] = -1;
  }

  int inontraite = 0;
  int x = 0;
  int racine = 0; //choisie arbitrairement

  d[racine] = 0;
  pere[racine] = racine;


  while((inontraite = existenontraite(traite, n)) != -1){
    
    x = minxnontraite(traite, d, n, inontraite);
    traite[x] = 1;
    
    for(int i = 0 ; i < (int)voisin[x].size() ; i++){

      int y = voisin[x][i];	

      float lxy = distance(&point[x], &point[y]);

      if(traite[y] == 0 && d[y] > d[x] + lxy){
        d[y] = d[x] + lxy;
        pere[y] = x;
      }
    }
  }
  delete[] d;
  delete[] traite;
}

int existenontraite(int traite[], int n){

	for (int i = 0; i < n; ++i)
	{
		if(traite[i] == 0)
			return i;
	}
	return -1;
}

int minxnontraite(int traite[], float d[], int n, int inontraite){
	int minx = inontraite;

	for (int i = inontraite; i < n; ++i)
	{
		if(traite[i] == 0 && d[i] < d[minx]){
			minx = i;
		}
	}
	return minx;
}