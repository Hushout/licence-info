#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int random(int n);
void grapherandom(int n, int m, int edge[][2]);
void printgraphe(int m, int edge[][2]);
void composante(int n, int m, int edge[][2], int comp[]);
void printcomposante(int n, int comp[]);
void ecrituretaille(int n, int m, int comp[]);
void compote(int n, int m, int edge[][2], int comp[]);
void swap(int& x, int& y);

int main(int argc, char** argv)
{
   if(argc == 3){

  srand(time(NULL));

  int n = atoi(argv[1]);     // Nombre de sommets.	
  int m = atoi(argv[2]);     // Nombre d'aretes.
  int edge[m][2];    // Tableau des aretes.
  int comp[n];       // comp[i] est le numero de la composante contenant i.
  int comp2[n];
  
  clock_t time;
  
  grapherandom(n, m, edge);
  printgraphe(m, edge);
  time = clock();
  composante(n, m, edge, comp);
  time = clock() - time;
  float tcomp = (float)time / CLOCKS_PER_SEC;
  
  time = clock();
  compote(n, m, edge, comp2);
  time = clock() - time;
  float tcomp2 = (float)time / CLOCKS_PER_SEC;
  
  cout << endl;

  cout << "comp = "; 
  printcomposante(n, comp);
  cout << endl;

  cout << "comp2 = "; 
  printcomposante(n, comp2);
  cout << endl;
  
  cout <<"Temps d'execution composante = " << tcomp << endl;
  cout <<"Temps d'execution compote = " <<  tcomp2 << endl;
  
  cout << endl;
  ecrituretaille(n, m, comp);
  cout << endl;
  }
  else{
    cout << "Erreur: entrez la n sommets puis m aretes en paramètre" << endl;
  }
  return EXIT_SUCCESS;
}

//Ex1:
void grapherandom(int n, int m, int edge[][2]){
  for(int i = 0; i < m ; i++){
    edge[i][0] = rand() % n;
    edge[i][1] = rand() % n;
  }
}

void printgraphe(int m, int edge[][2]){
  cout << "graphe = {";
  for(int i = 0; i < m ; i++){
    if(i == m - 1)
      cout << "{" << edge[i][0] << ", " << edge[i][1] << "}";
    else
      cout << "{" << edge[i][0] << ", " << edge[i][1] << "}, ";
  }
  cout << "}" << endl;
}

//Ex2:
void composante(int n, int m, int edge[][2], int comp[]){
  int aux = 0;

  for(int i = 0 ; i < n ; i++){
    comp[i] = i;
  }
  
  for(int j = 0; j < m; j++){
    
    if(comp[edge[j][0]] != comp[edge[j][1]]){
      
      aux = comp[edge[j][0]];
      
      for(int k = 0; k < n; k++){
	if(comp[k] == aux){
	  comp[k] = comp[edge[j][1]];
	}
      }
    }
  }
}


void printcomposante(int n, int comp[]){
  cout << "{";
  for(int i = 0; i < n ; i++){
    if(i == n - 1)
      cout << comp[i];
    else
      cout << comp[i] << ", ";
  }

  cout << "}" << endl;
}

//Ex3:
void ecrituretaille(int n, int m, int comp[]){
  int compteSommets[n] = {0};
  int compteTaille[n] = {0};

  for(int i = 0; i < n ; i++){
    compteSommets[comp[i]]++;
  }

  for(int i = 0; i < n ; i++){
    compteTaille[compteSommets[i]]++;
  }

  for(int i = 1 ; i < n ; i++){
      if(i == 1){
	cout << "Il y a " << compteTaille[i] << " points isoles." << endl;
      }
      else if(compteTaille[i] != 0){
	cout << "Il y a " << compteTaille[i] << " de taille " << i << "." << endl;
      }
  }
}

//Ex4:

void swap(int& x, int& y){
  int temp = x;
  x = y;
  y = temp;
}

void compote(int n, int m, int edge[][2], int comp[]){
  int aux1 = 0;
  int aux2 = 0;
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
}
  

//Ex5:

/* La proporsion des points isolés est d'a peu près 13% */
