
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

int main(){
int n;                   //Le nombre de points.
cout << "Entrer le nombre de points: ";
cin >> n;

int dmax=50;             // La distance jusqu'a laquelle on relie deux points.

vector<int> voisin[n];   // Les listes de voisins.          
int point[n][2];         // Les coordonnees des points.
int arbre[n-1][2];       // Les aretes de l'arbre de Dijkstra .
int pere[n];             // La relation de filiation de l'arbre de Dijkstra.


return 0;
}
