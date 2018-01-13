#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;


int ** Matrice(int p, int q){ //Creation dynamique d'une matrice
 int** T= new int* [p];
  for(int i=0; i<p; i++){
    T[i]=new int [q];
  }
  return T;
}


void EffaceMatrice(int p,  int ** T){ //Desallocation d'une matrice
  for(int i=0; i<p; i++){
    delete[] T[i];
  }
  delete[] T;
}



void RemplitMatrice(int p, int q, int** T){ //Exemple d'utilisation
  for(int i=0;i<p; i++){
    for(int j=0;j<q;j++){
      T[i][j]=i+j;
    }
  }
}


void AfficheMatrice(int p, int q, int** T){ //Affichage
  for(int i=0;i<p;i++){
    for(int j=0;j<q;j++){
    cout << T[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl; 
}



int main(){
  int n;
  cout << "valeur de n: "<< endl;
  cin >> n;

  int** T= Matrice(n,n);
  RemplitMatrice(n,n,T);
  AfficheMatrice(n,n,T);
  EffaceMatrice(n,T);


}
