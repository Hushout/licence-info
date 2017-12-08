#include <iostream>
#include <vector>
#include <cstdlib>
#include "villes.h"
#include <map>


using namespace std;

const int n=41;
const int n2 = 6;
const int inf=9999;                    //La valeur infinie.    

void floyd_warshall(int longueur[][n], int dist[][n], int chemin[][n]);
void printchemin(int chemin[][n]);

void itineraire(int i, int j, int chemin[][n]);

void fermeturetransitive(int arc[][6], int fermeture[][6]);
void printfermeture(int fermeture[][6]);

void compfortconnexe(int n, int fermeutre[][6]);

int main(int argc, char** argv){

	if(argc == 3){

	int (*longueur)[n] = new int[n][n];
	initlongueur(longueur);

    int arc[6][6]={{0,0,0,1,0,1},//La matrice d'adjacence du graphe oriente D.
				   {1,0,1,1,0,0},
				   {0,0,0,1,0,0},
				   {0,0,0,0,1,1},
				   {0,0,1,0,0,1},
				   {0,0,1,0,0,0}};

    int fermeture[6][6];         // La matrice de la fermeture transitive de D.

    int (*dist)[n] = new int[n][n];                      //Le tableau des distances.
    int (*chemin)[n] = new int[n][n];                    //Le tableau de la premiere etape du chemin de i a j.

    floyd_warshall(longueur, dist, chemin);
    //printchemin(chemin);
    int i = atoi(argv[1]);
    int j = atoi(argv[2]);

    itineraire(i, j, chemin);

    fermeturetransitive(arc, fermeture);
  	printfermeture(fermeture);

  	compfortconnexe(6, fermeture);

  	//cout << "Les chemin est possible " << fermeture[i][j] << endl;

	}
	else{
		cout << "Erreur d'argument: " << argv[0] << " <i> <j>  (0 <= j i <= 40)" << endl;
	}

	return 0;
}

void floyd_warshall(int longueur[][n], int dist[][n], int chemin[][n]){

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){

			if(longueur[i][j] != inf){
				dist[i][j] = longueur[i][j];
				chemin[i][j] = j;
			}
			else{
				dist[i][j] = inf;
				chemin[i][j] = -1;   
			}
		}
	}

	for(int k = 0; k < n ; k++){
		for(int i = 0 ; i < n ; i++){
			for(int j = 0 ; j < n ; j++){

				if(dist[i][j] > dist[i][k] + dist[k][j]){
          			dist[i][j] = dist[i][k] + dist[k][j]; // k est un raccourci pour aller de i à j
          			chemin[i][j] = chemin[i][k]; 
      			}
  			}
  		}
	}

	for(int i = 0 ; i < n ; i++){
		if(dist[i][i] < 0){
			cout << "Il existe un cycle orienté de poids < 0" << endl;
			return;
		}
	}
}

void printchemin(int chemin[][n]){
	cout << "{";
	for(int i = 0 ; i < n ; i++){
		cout << "{ ";
		for(int j = 0 ; j < n ; j++){
			cout << chemin[i][j] << " ";
		}
		cout << "}";
	}
	cout << "}" << endl;
}

void itineraire(int i, int j, int chemin[][n]){
	int next = chemin[i][j];
	cout << "Depart: " << i << endl;
	cout << "Destination: " << j << endl;
	cout << "Itineraire: " << i << " " << next << " ";

	while(next != j){
		next = chemin[next][j];
		cout << next << " ";
	}
	cout << endl;
}

void fermeturetransitive(int arc[][6], int fermeture[][6]){

	int n = 6;

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){
			fermeture[i][j] = arc[i][j];
		}
	}

	for(int k = 0; k < n ; k++){
		for(int i = 0 ; i < n ; i++){
			for(int j = 0 ; j < n ; j++){

				if(arc[i][k] && arc[k][j]){
         			fermeture[i][j] = 1; 
      			}
  			}
		}
	}
}

void printfermeture(int fermeture[][6]){
	int n = 6;
	cout << "{" << endl;
	for(int i = 0 ; i < n ; i++){
		cout << "{ ";
		for(int j = 0 ; j < n ; j++){
			cout << fermeture[i][j] << " ";
		}
		cout << "}" << endl;
	}
	cout << "}" << endl;
}

void compfortconnexe(int n, int fermeture[][6]){

	vector<int> comp(n);

	for(int i = 0 ; i < n ; i++){
    	comp[i] = i;
  	}

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){
			if(fermeture[i][j] && fermeture[j][i]){
				int aux = comp[i];
				for(int k = 0; k < n; k++){
					if(comp[k] == aux){
		  				comp[k] = comp[j];
					}
      			}
			}
		}
	}

	map<int, vector<int>> mp;
	map<int, vector<int>>::iterator it;

	for(int i = 0 ; i < n ; i++){
		it = mp.find(comp[i]);
		if(it != mp.end()){
			mp[comp[i]].push_back(i);
		}
		else{
			vector<int> newv;
			newv.push_back(i);
			mp[comp[i]] = newv;
		}
	}
	cout << "Les composantes fortement connexes sont: ";
	for(map<int, vector<int>>::iterator it = mp.begin() ; it != mp.end() ; it++){
		cout << "{ ";
		for(int i = 0 ; i < (int)it->second.size() ; i++){
			cout << it->second[i] << " ";
		}
		cout << "} ";
	}
	cout << endl;
}
