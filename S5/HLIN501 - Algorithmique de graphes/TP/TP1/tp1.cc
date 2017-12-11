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
void composanteopti(int n, int m, int edge[][2], int comp[]);
void swap(int& x, int& y);

int main(int argc, char** argv)
{
  if(argc >= 3){

    srand(time(NULL));

    bool onlyopti = false;
    bool printall = false;

    for(int i = 0 ; i < argc ; i++){
      string s(argv[i]);
      if(s == "-o")
        onlyopti = true;
      if(s == "-p")
        printall = true;
    }

    clock_t time;
    float tcomp = -1;
    float tcompopti = -1;

    int n = atoi(argv[1]);     // Nombre de sommets.  
    int m = atoi(argv[2]);     // Nombre d'aretes.

    int* comp = NULL;

    cout << "-Allocation mémoire..." << endl;
    time = clock();
    int (*edge)[2] = new int[m][2];    // Tableau des aretes.
    if(!onlyopti)
      comp = new int[n];       // comp[i] est le numero de la composante contenant i.
    int* compopti = new int[n];
    time = clock() - time;
    cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;
    
    cout << "-Generation du graphe aléatoire..." << endl;
    time = clock();
    grapherandom(n, m, edge);
    time = clock() - time;
    if(printall)
      printgraphe(m, edge);
    cout << "Fait en " << (float)time / CLOCKS_PER_SEC << "s" << endl << endl;

    if(!onlyopti){
      cout << "-Application de composante..." << endl;
      time = clock();
      composante(n, m, edge, comp);
      time = clock() - time;
      tcomp = (float)time / CLOCKS_PER_SEC;
      cout << "comp = "; 
      if(printall)
        printcomposante(n, comp);
      cout << "Fait en " << tcomp << "s" << endl << endl;
    }

    cout << "-Application de composanteopti..." << endl;
    time = clock();
    composanteopti(n, m, edge, compopti);
    time = clock() - time;
    cout << "compopti = ";
    if(printall)
      printcomposante(n, compopti);
    tcompopti = (float)time / CLOCKS_PER_SEC;
    cout << "Fait en " << tcompopti << "s" << endl << endl;

    ecrituretaille(n, m, compopti);
    cout << endl;

    if(!onlyopti)
      cout <<"Temps d'execution composante = " << tcomp << "s" << endl;
    cout <<"Temps d'execution composanteopti = " <<  tcompopti << "s" << endl;

    cout << endl;

    delete[] edge;
    delete[] compopti;
    if(!onlyopti)
      delete[] comp;

  }
  else{
    cout << endl << "Usage: " << argv[0] << " <sommets> <aretes> <option1> <option2> ..." << endl << endl;
    cout << "DESCRIPTION:" << endl;
    cout << "    Ce programme calcul les composantes connexes d'un graphe generé aléatoirement et les affichent." << endl << endl;
    cout << "ARGUMENTS:" << endl;
    cout << "    <sommets> => le nombre de sommets du graphe." << endl;
    cout << "    <aretes> => le nombre d'aretes du graphe." << endl;
    cout << "    <option> => les options a appliquer au programme." << endl << endl;
    cout << "OPTIONS:" << endl;
    cout << "    -o => execute uniquement composanteopti." << endl;
    cout << "    -p => affiche les structures a chaque etapes de calcul." << endl << endl;
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
      cout << "{" << edge[i][0] << " " << edge[i][1] << "} ";
  }
  cout << "\b}" << endl;
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
      cout << comp[i] << " ";
  }

  cout << "\b}" << endl;
}

//Ex3:
void ecrituretaille(int n, int m, int comp[]){
  int* compteSommets = new int[n];
  int* compteTaille = new int[n];
  
  for(int i = 0; i < n ; i++){
    compteSommets[i] = 0;
    compteTaille[i] = 0;
  }

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
	     cout << "Il y a " << compteTaille[i] << " composantes de taille " << i << "." << endl;
      }
  }

  delete[] compteSommets;
  delete[] compteTaille;
}

//Ex4:

void swap(int& x, int& y){
  int temp = x;
  x = y;
  y = temp;
}

void composanteopti(int n, int m, int edge[][2], int comp[]){
	
  int aux1 = 0, aux2 = 0;
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
