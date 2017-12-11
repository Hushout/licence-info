#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "villes.h"
#include <ctime>
#include <set>
#include <map>


using namespace std;

const int tailleLongueur = 100;			//nb sommets de longueur[tailleLongueur][tailleLongueur], valeur modifiable, le programme s'adaptera.
const int tailleArc = 500;				//nb sommets de arc[tailleArc][tailleArc], valeur modifiable, le programme s'adaptera.

const int inf=9999;                    	//valeur infinie, à ne pas modifier pour le bon déroulement du programme;


void floyd_warshall(int longueur[][tailleLongueur], int dist[][tailleLongueur], int chemin[][tailleLongueur]);
void printchemin(int chemin[][tailleLongueur]);
void itineraire(int i, int j, int chemin[][tailleLongueur]);

void fermeturetransitive(int arc[][tailleArc], int fermeture[][tailleArc]);
void printfermeture(int fermeture[][tailleArc]);
void compfortconnexe(int fermeutre[][tailleArc]);

void randomlongueur(int longueur[][tailleLongueur]);
void randomarc(int arc[][tailleArc], int nbarc);

bool findchemin(int argc, char** argv);
bool findcomp(int argc, char** argv);

int main(int argc, char** argv){

	srand(time(NULL));
	
	bool donechemin = findchemin(argc, argv);
	bool donecomp = findcomp(argc, argv);

	if(!(donechemin || donecomp)){
		cout << endl << "Usage: " << argv[0] << " <choix> <options>" << endl << endl;
	    cout << "DESCRIPTION:" << endl;
	    cout << "    Ce programme calcul aux choix un itineraire de plus cours chemin dans un graphe orienté et/ou les composantes fortement connexes d'un graphe orienté." << endl << endl;
	    cout << "ARGUMENTS:" << endl;
	    cout << "    <choix> => ce qu'il faut calculer -i <sommeti> <sommetj> et/ou -c <nbarcs>." << endl;
	    cout << "    <options> => les options a appliquer au programme." << endl << endl;
		cout << "OPTIONS:" << endl;
		cout << "    -i <sommeti> <sommetj> => trouve un itineraire de i à j sur un graphe orienté de " << tailleLongueur << " sommets dont les arcs sont tires au hasard." << endl;
		cout << "    -c <nbarcs> => affiche les composantes fortement connexes d'un graphe orienté de " << tailleArc << " sommets dont les arcs sont tires au hasard." << endl;
		cout << "    -p => affiche le contenu des structures alloués à chaque etapes de Calcul (si des structures on été allouées)." << endl << endl;
	}
	return 0;
}

void floyd_warshall(int longueur[][tailleLongueur], int dist[][tailleLongueur], int chemin[][tailleLongueur]){
	
	int n = tailleLongueur;

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

void printchemin(int chemin[][tailleLongueur]){
	int n = tailleLongueur;
	for(int i = 0 ; i < n ; i++){
		cout << "{";
		for(int j = 0 ; j < n ; j++){
			cout << chemin[i][j] << " ";
		}
		cout << "\b}" << endl;
	}
}

void itineraire(int i, int j, int chemin[][tailleLongueur]){

	int next = i;
	cout << "Depart: " << i << endl;
	cout << "Destination: " << j << endl;
	cout << "Itineraire: " << i << " ";

	while(next != j && next != -1){
		next = chemin[next][j];

		if(next != -1)
			cout << next << " ";
		else
			cout << endl << "Chemin impossible, réexecutez le programme pour faire un nouveau tirage des arcs";
	}
	cout << endl;
}

void fermeturetransitive(int arc[][tailleArc], int fermeture[][tailleArc]){

	int n = tailleArc;

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

void printfermeture(int fermeture[][tailleArc]){
	
	int n = tailleArc;
	for(int i = 0 ; i < n ; i++){
		cout << "{";
		for(int j = 0 ; j < n ; j++){
			cout << fermeture[i][j] << " ";
		}
		cout << "\b}" << endl;
	}
}

void compfortconnexe(int fermeture[][tailleArc]){

	int n = tailleArc;

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

	map<int, vector<int> > mp;
	map<int, vector<int> >::iterator it;

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

	for(map<int, vector<int> >::iterator it = mp.begin() ; it != mp.end() ; it++){
		cout << "{";
		for(int i = 0 ; i < (int)it->second.size() ; i++){
			cout << it->second[i] << " ";
		}
		cout << "\b}";
	}
	cout << endl;
}

void randomlongueur(int longueur[][tailleLongueur]){
	
	int n = tailleLongueur;

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < n ; j++){
			longueur[i][j] = inf;
		}
		longueur[i][i] = 0;
	}

	for(int i = 0 ; i < n ; i++){
		int k1 = i;
		int k2 = i;
		while(k1 == i || k2 == k1){
			if(k1 == i)
				k1 = rand() % n;
			k2 = rand() % n;
		}
		longueur[i][k1] = 1;
		longueur[i][k2] = 1;
	}
}

void randomarc(int arc[][tailleArc], int nbarc){

	int n = tailleArc;
	vector<int> ivisitable(n);
	vector<vector<int> > jvisitable(n);

	for(int i = 0 ; i < n ; i++)
		ivisitable[i] = i;

	for(int i = 0 ; i < n ; i++)
		jvisitable[i] = ivisitable;

	while(nbarc > 0){
		int indexi = rand() % ivisitable.size();
		int i = ivisitable[indexi];

		int indexj = rand() % jvisitable[i].size();
		int j = jvisitable[i][indexj];

		arc[i][j] = 1;

		jvisitable[i].erase(jvisitable[i].begin() + indexj);
		
		if(jvisitable[i].size() == 0)
			ivisitable.erase(ivisitable.begin() + indexi);

		nbarc--;
	}
}

bool findchemin(int argc, char** argv){

	int index = 0;
	bool affiche = false;
	for(int i = 0 ; i < argc ; i++){
		string s(argv[i]);
		if(s == "-i")
			index = i;
		else if(s == "-p")
			affiche = true;
	}
	if(index && index + 2 <= argc){

		clock_t time;

		cout << endl << "ITINERAIRE:" << endl << endl;

    	cout << "-Allocation mémoire..." << endl;
    	time = clock();
		int (*longueur)[tailleLongueur] = new int[tailleLongueur][tailleLongueur];
		int (*dist)[tailleLongueur] = new int[tailleLongueur][tailleLongueur];                      //Le tableau des distances.
	    int (*chemin)[tailleLongueur] = new int[tailleLongueur][tailleLongueur];                    //Le tableau de la premiere etape du chemin de i a j.
	    time = clock() - time;
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

	    cout << "-Generation des arcs aleatoirement sur " << tailleLongueur << " sommets..." << endl;
		randomlongueur(longueur);
		if(affiche){
			cout << "longueur = ";
			printchemin(longueur);
		}
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		cout << "-Application de floyd_warshall..." << endl;
	    floyd_warshall(longueur, dist, chemin);
	    if(affiche){
	    	cout << "chemin = ";
	    	printchemin(chemin);
	    }
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;
	   	
	   	int i = atoi(argv[index + 1]); int j = atoi(argv[index + 2]);

	   	cout << "-Calcul de l'itineraire le plus court de " << i << " a " << j << "..." << endl;
	    itineraire(i, j, chemin);
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;
	    return true;
	}
	return false;
}

bool findcomp(int argc, char** argv){
	int index = 0;
	bool affiche = false;
	for(int i = 0 ; i < argc ; i++){
		string s(argv[i]);
		if(s == "-c")
			index = i;
		else if(s == "-p")
			affiche = true;
	}
	if(index && index + 1 <= argc){

		clock_t time;

				
		cout << endl << "COMPOSANTES:" << endl << endl;

		cout << "-Allocation memoire..." << endl;
		time = clock();
		int (*arc)[tailleArc] = new int[tailleArc][tailleArc];
		int (*fermeture)[tailleArc] = new int[tailleArc][tailleArc];
		time = clock() - time;
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		int nbarcs = atoi(argv[index + 1]);

		cout << "-Generation de " << nbarcs << " arcs aleatoirement sur " << tailleArc << " sommets..." << endl;
		time = clock();
		randomarc(arc, nbarcs);
		time = clock() - time;
		if(affiche){
			cout << "arc = ";
			printfermeture(arc);
		}
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

		cout << "-Calcul de la fermeture transitive..." << endl;
		time = clock();
	    fermeturetransitive(arc, fermeture);
	    time = clock() - time;
	    if(affiche){
	    	cout << "fermeture = ";
	   		printfermeture(fermeture);
	    }
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

	  	cout << "-Calcul et affichage des composantes fortement connexes..." << endl;
	  	time = clock();
	  	compfortconnexe(fermeture);
	  	time = clock() - time;
		cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;
	    return true;
	}
	return false;
}