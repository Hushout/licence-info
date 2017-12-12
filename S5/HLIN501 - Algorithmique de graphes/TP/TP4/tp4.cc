
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

	if(argc >= 3){

		srand(time(NULL));

		bool printall = false;
		int n = atoi(argv[1]);                   //Le nombre de points.
		int dmax = atoi(argv[2]);             // La distance jusqu'a laquelle on relie deux points.
		clock_t time;


		for(int i = 0 ; i < argc ; i++){
	      string s(argv[i]);
	      if(s == "-p")
	        printall = true;
	    }

    
    	cout << "-Allocation mémoire..." << endl;
   		time = clock();
		vector<int>* voisin = new vector<int>[n];   // Les listes de voisins.
		coord *point = new coord[n];         // Les coordonnees des points.
		int* pere = new int[n];             // La relation de filiation de l'arbre de Dijkstra.
		time = clock() - time;
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		cout << "-Generation des points aleatoire..." << endl;
		time = clock();
		pointrandom(n, point);
		time = clock() - time;
		if(printall)
			printpoint(n, point);
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		cout << "-Creation de la liste des voisins..." << endl;
		time = clock();
		voisins(n, dmax, point, voisin);
		time = clock() - time;
		if(printall)
			printvoisins(n, voisin);
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		cout << "-Application de dijkstra..." << endl;
		time = clock();
		dijkstra(n, voisin, point, pere);
		time = clock() - time;
		if(printall){
			cout << "pere = ";
			printarray(n, pere);
		}
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		cout << "-Sorti du graphe dans Voisins.pdf et de dijkstra dans Parcours.pdf..." << endl;
		time = clock();
		AffichageGraphiqueVoisins(n, point, voisin); //output => Voisins.ps
		AffichageGraphiqueParcours(n, point, pere); //output => Parcours.ps 
		system("ps2pdf Voisins.ps");
		system("ps2pdf Parcours.ps");
		time = clock() - time;
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;


		delete[] voisin;
		delete[] point;
		delete[] pere;
	}
	else{
		cout << endl << "Usage: " << argv[0] << " <sommets> <dist> <options>" << endl << endl;
	    cout << "DESCRIPTION:" << endl;
	    cout << "    Ce programme calcul un arbre de plus courts chemins issu d'un sommets dans un graphe generé aléatoirement et le sort en pdf." << endl << endl;
	    cout << "ARGUMENTS:" << endl;
	    cout << "    <sommets> => le nombre de sommets du graphe." << endl;
	    cout << "    <dist> => la distance maximal pour qu'une arete ce forme entre deux sommets du graphe." << endl;
	    cout << "    <options> => les options a appliquer au programme." << endl << endl;
	    cout << "OPTIONS:" << endl;
	    cout << "    -p => affiche les structures a chaque etape de calcul." << endl << endl;
	}
	return 0;
}

void printarray(int n, int array[]){
  cout << "{";
  for(int i = 0 ; i < n ; i++){
    cout << array[i] << " ";
  }
  cout << "\b}\n";
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
		cout << "{" << point[i].abs << " " << point[i].ord << "} ";
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
		cout << "{";
		for(int j = 0 ; j < (int)voisin[i].size() ; j++){
			cout << voisin[i][j] << " ";
		}
		cout << "\b} ";
	}
	cout << "\b}\n";
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
  int racine = 0; //choisie arbitrairement

  d[racine] = 0;
  pere[racine] = racine;


  while((inontraite = existenontraite(traite, n)) != -1){
    
    int x = minxnontraite(traite, d, n, inontraite);
    traite[x] = 1;
    
    for(int i = 0 ; i < (int)voisin[x].size() ; i++){

      int y = voisin[x][i];	

      float lxy = distance(&point[x], &point[y]);

      if(!traite[y] && d[y] > d[x] + lxy){
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