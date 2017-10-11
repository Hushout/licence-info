#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

void randomarray(int n, int sum, int array[]);

void printarray(int n, int array[]);

void voisinsrandom(int n, int m, vector<int> voisins[]);
void printvoisins(int n, vector<int> voisins[]);
bool isIn(int n, vector<int> vect);

void parcourslargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]);

void ecritureniveaux(int n, int niveau[]);

void parcoursprofondeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]);

int main(int argc, char** argv){
  srand(time(NULL));
  if(argc == 3){
    int n = atoi(argv[1]);             //Le nombre de sommets.
    int m = atoi(argv[2]);             // Le nombre d'aretes.
    
    vector<int> voisins[n];	// Les listes des voisins. 
    int pere[n];            // L'arbre en largeur.
    int ordre[n];           // L'ordre de parcours.
    int niveau[n];          // Le niveau du point.
    
    voisinsrandom(n, m, voisins);
    printvoisins(n, voisins);

    parcourslargeur(n, voisins, niveau, ordre, pere);
    cout << "pere:" << endl;
    printarray(n, pere);
    cout << "ordre:" << endl;
    printarray(n, ordre);
    cout << "niveau:" << endl;
    printarray(n, niveau);
  }
  else{
    cout << "Erreur d'argument: " << argv[0] << " <sommets> <aretes> <options> (-p => affiche structure terminal)" << endl;
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
  cout << "{";
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

  int* occ = new int[n];


 
  for(int i = 0 ; i < n ; i++){
    dv[i] = 0;
    occ[i] = 0;
    int j = 0;

    while(j < (int)voisins[i].size()){
    	occ[voisins[i][j]]++;
    	j++;
    }
  }
  
  int racine = 0; //a trouver
  int max = 0;

  for(int i = 0 ; i < n ; i++){
  	if(occ[i] > max){
  		max = occ[i];
  		racine = i;
  	}
  }

  int t = 2;
  dv[racine] = 1;
  ordre[racine] = 1;
  pere[racine] = racine;
  niveau[racine] = 0;

  vector<int> AT;
  AT.push_back(racine);

  while(!AT.empty()){
    
    int v = AT.back();
    AT.pop_back();
    
    for(int i = 0 ; i < (int)voisins[v].size() ; i++){
      
      int x = voisins[v][i];
      
      if(dv[x] == 0){
      
	dv[x] = 1;
	vector<int>::iterator it;
	it = AT.begin();
	AT.insert(it, x);
	ordre[x] = t; t+=1;
	pere[x] = v;
	niveau[x] = niveau[v] + 1;
      }
    }
  }
  
}

void ecritureniveaux(int n, int niveau[]){

}
