#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstring>
#include <ctime>
#include "Affichage.h"

using namespace std;

void randomarray(int n, int sum, int array[]);
void printarray(int n, int array[]);

void voisinsrandom(int n, int m, vector<int> voisins[]);
void printvoisins(int n, vector<int> voisins[]);
bool isIn(int n, vector<int> vect);

void parcourslargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]);
void parcoursprofondeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]);
void ecritureniveaux(int n, int niveau[]);

void pointrandom(int n, coord point[]);
void printpoint(int n, coord point[]);
void createvoisins(int n, coord point[], vector<int> voisins[], int maxdist);

int main(int argc, char** argv){
  if(argc >= 3){
    
    srand(time(NULL));

    int n = atoi(argv[1]);             //Le nombre de sommets.
    int m = atoi(argv[2]);             //Le nombre d'aretes.

    bool printall = false;
    bool plargeur = false;

    for(int i = 0 ; i < argc ; i++){
      string s(argv[i]);
      if(s == "-p")
        printall = true;
      if(s == "-l")
        plargeur = true;
    }

    clock_t time;
    
    cout << "-Allocation mémoire..." << endl;
    time = clock();
    vector<int>* voisins = new vector<int>[n];	// Les listes des voisins. 
    int* pere = new int[n];            // L'arbre en largeur.
    int* ordre = new int[n];           // L'ordre de parcours.
    int* niveau = new int[n];          // Le niveau du point.
    coord* point = new coord[n];
    time = clock() - time;
    cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl<<endl;

    cout << "-Generation des points aleatoire..." << endl;
    time = clock();
    pointrandom(n, point);
    time = clock() - time;
    if(printall)
      printpoint(n, point);
    cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl<<endl;

    cout << "-Creation de la liste des voisins..." << endl;
    time = clock();
    createvoisins(n, point, voisins, m);
    time = clock() - time;
    if(printall)
      printvoisins(n, voisins);
    cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl<<endl;


    if(!plargeur){
      cout << "-Parcours en profondeur de voisins..." << endl;
      time = clock();
      parcoursprofondeur(n, voisins, niveau, ordre, pere);
      time = clock() - time;
    }
    else{
      cout << "Parcours en largeur de voisins..." << endl;
      time = clock();
      parcourslargeur(n, voisins, niveau, ordre, pere);
      time = clock() - time;
    }

    if(printall){
      cout << "pere = ";
      printarray(n, pere);
      cout << endl << "ordre = ";
      printarray(n, ordre);
      cout << endl << "niveau = ";
      printarray(n, niveau);
    }
    cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl<<endl;

    ecritureniveaux(n, niveau);
    cout << endl;
    
    cout << "-Sorti du graphe dans Voisins.pdf et du parcour dans Parcours.pdf..." << endl;
    time = clock();
	  AffichageGraphiqueVoisins(n, point, voisins); //output => Exemple.ps
    system("ps2pdf Voisins.ps"); //create .pdf with the .ps file
	  AffichageGraphiqueParcours(n, point, pere); //output => Exemple.ps
    system("ps2pdf Parcours.ps"); //create .pdf with the .ps file
    time = clock() - time;
    cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl<<endl;

    delete[] voisins;	
    delete[] pere;           
    delete[] ordre;
    delete[] niveau;          
    delete[] point;
  }
  else{
    cout << endl << "Usage: " << argv[0] << " <sommets> <carrelongueurmaxaretes> <option>" << endl << endl;
    cout << "OPTION:" << endl;
    cout << "    -p => affiche les structures a chaque etape de calcul." << endl << endl;
    cout << "    -l => execute un parcour en largeur au lieux d'un parcours en profondeur." << endl << endl;
  }

  return 0;
}

void printarray(int n, int array[]){
  cout << "{";
  for(int i = 0 ; i < n ; i++){
    cout << array[i] << " ";
  }
  cout << "\b\b}" << endl;
}

void voisinsrandom(int n, int m, vector<int> voisins[]){
  
  int taille = 0;
  while(taille < m){
    
    int numVois = rand() % n;
    int v = rand() % n;
    
    while(v == numVois){
      v = rand() % n;
    }

    if(!isIn(v, voisins[numVois])){
      voisins[numVois].push_back(v);
      voisins[v].push_back(numVois);
    }

    taille++;
  }
}

bool isIn(int n, vector<int> vect){
  for(int i= 0; i < (int)vect.size(); i++){
    if(n == vect[i]){
      return true;
    }
  }
  return false;
}

void randomarray(int n, int m, int array[]){
  int sum = 0;
  
  // Generate n random numbers
  for (int i = 0; i < n; i++){
    array[i] = rand();
    sum += array[i];
  }
  
  // Normalize sum to m
  for (int i = 0; i < n; i++){
    array[i] /= sum * m;
  }
}

void printvoisins(int n, vector<int> voisins[]){
  cout << "voisins = {";
  for(int i = 0 ; i < n ; i++){
    cout << "{ ";
    for(int j = 0 ; j < (int)voisins[i].size() ; j++){
      cout << voisins[i][j] << " ";
    }
    cout << "}";
  }
  cout << "}\n";
}

void parcourslargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]){
  int* dv = new int[n];
  
  for(int i = 0 ; i < n ; i++){
    dv[i] = 0;
    ordre[i] = -1;
    pere[i] = -1;
    niveau[i] = -1;
  }
  
  int racine = 0; //choisie arbitrairement

  int t = 2;
  dv[racine] = 1;
  ordre[racine] = 1;
  pere[racine] = racine;
  niveau[racine] = 0;

  queue<int> AT;
  AT.push(racine);

  while(!AT.empty()){
    
    int v = AT.front();
    AT.pop();
    
    for(int i = 0 ; i < (int)voisins[v].size() ; i++){
      
      int x = voisins[v][i];
      
      if(dv[x] == 0){
        
        dv[x] = 1;
        AT.push(x);
        ordre[x] = t; t+=1;
        pere[x] = v;
        niveau[x] = niveau[v] + 1;
      }
    }
  }
  delete[] dv;
}

void parcoursprofondeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]){
  int* dv = new int[n];
  
  for(int i = 0 ; i < n ; i++){
    dv[i] = 0;
    ordre[i] = -1;
    pere[i] = -1;
    niveau[i] = -1;
  }
  
  int racine = 0; //choisie arbitrairement

  int t = 2;
  dv[racine] = 1;
  ordre[racine] = 1;
  pere[racine] = racine;
  niveau[racine] = 0;

  stack<int> AT;
  AT.push(racine);

  while(!AT.empty()){
    
    int v = AT.top();
    AT.pop();
    
    for(int i = 0 ; i < (int)voisins[v].size() ; i++){
      
      int x = voisins[v][i];
      
      if(dv[x] == 0){
        
        dv[x] = 1;
        AT.push(x);
        ordre[x] = t; t+=1;
        pere[x] = v;
        niveau[x] = niveau[v] + 1;
      }
    }
  }
  delete[] dv;
}

void ecritureniveaux(int n, int niveau[]){
	int* nbNiv = new int[n];
	int nbNotIn = 0;
	
	for(int i = 0 ; i < n ; i++){
		nbNiv[i] = -1;
	}
	for(int i = 0 ; i < n ; i++){
		if(niveau[i] != -1)
			nbNiv[niveau[i]]++;
		else
			nbNotIn++;
	}
	for(int i = 0 ; i < n ; i++){
		if(nbNiv[i] != -1 && nbNiv[i] != 0)
      cout << "Il y a " << nbNiv[i] << " sommets au niveau " << i << endl;
  }
  if(nbNotIn)
    cout << "Il y a " << nbNotIn << " sommets qui ne sont pas dans la composante de 0." << endl;

  delete[] nbNiv;
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
  cout << "point = {";
  for(int i = 0 ; i < n ; i++){
    cout << "{" << point[i].abs << " " << point[i].ord << "} ";
  }
  cout << "\b}\n";
}

void createvoisins(int n, coord point[], vector<int> voisins[], int maxdist){

  for(int i = 0 ; i < n ; i++){
   for(int j = 0 ; j < n ; j++){
    if(j != i){
     int dist = pow(point[j].abs - point[i].abs , 2) + pow(point[j].ord - point[i].ord , 2);
     if(dist <= maxdist){
      voisins[i].push_back(j);
    }
  }
}
}
}