#include <iostream>
#include <fstream>
#include <stdlib.h>  // pour rand
#include <assert.h>
#include "outilsTab5.h"

using namespace std;



int* copieTab(int* T, size_t t){
  int* Tc;
  Tc=new int[t];
  for( size_t i=0;i<t;i++)Tc[i]=T[i];
  return Tc;
}

int* genTab(size_t n){
    int* T; 
    T=new int[n];
    for (size_t i=0;i<n;i++) T[i]=rand();
    return T;
}

void afficheTab(int* T,	size_t taille){
  cout << "\n[ ";
  for (size_t i=0;i<taille;i++) cout << T[i] << " ";
  cout << "]\n";
}

void echanger(int& a, int& b){int aux=a; a=b; b=aux; return;}

void fichierTemps(const char *  nomFic, size_t tMaxTab, size_t pas, void (*fTri)(int*,size_t))
{
    size_t taille;
    int* Tab;
    clock_t t1, t2;    
    ofstream fichier(nomFic,ios::out);

    if (fichier)
    {
        for (taille=pas; taille<=tMaxTab; taille=taille+pas){
            Tab=genTab(taille);
            t1=clock();
            (*fTri)(Tab,taille);
            t2=clock();
            fichier << taille <<" "<< (double)(t2-t1)/ CLOCKS_PER_SEC << endl;
        }
        fichier.close();
    }
    else cerr << " Problème ouverture fichier"<< endl;

    return ;
}



/* ********************** Les Tris *********************** */

/* Tri par insertion */
void triInsertion(int* T, size_t taille)
{
  int k = 0;
  int j = 0;
  for(int i = 0 ; i < taille ; i++){
    k = T[i];
    j = i;
    while( j > 0 && T[j - 1] > k){
      T[j] = T[j-1];
      j--;
    }
    T[j] = k;
  }
  return;
}




/* Tri par Sélection */
void triSelection(int* T, size_t taille)
{
  int min = 0;
  for(int i = 0 ; i < taille ; i++){
    min = i;
    for(int j = i + 1 ; j < taille ; j++){
      if(T[j] < T[min]){
	min = j;
      }
    }
    if(min != i){
      echanger(T[i], T[min]);
    }
  }
  return;
}




/* Tri par Tas */
size_t filsMax(int* T, size_t i, size_t iMax)
{
  if ((i*2+2>iMax) || (T[2*i+1]>T[2*i+2])) return 2*i+1;
  else return 2*i+2;
}
void triParTas(int* T, size_t taille)
{
  size_t i,j,k; 
  for (i=1;i<taille;i++){
    j=i;
    while(j>0 && T[(j-1)/2]<T[j]){
      echanger(T[j],T[(j-1)/2]);
      j=(j-1)/2;}}
  for (i=taille-1;i>0;i--){
    echanger(T[0],T[i]);
    j=0;
    while( (2*j+1<i) && T[filsMax(T,j,i-1)]>T[j]){
      k=filsMax(T,j,i-1);
      echanger(T[j],T[k]);
      j=k;} }
  return;
}
/*
int pivot(int* T, size_t deb, size_t fin){
  int pivot = T[fin];
  int j = deb;
  
  for(int i = deb ; i < fin ; i++){
    if(T[i] <= pivot){
      echanger(T[i], T[j]);
      j++;
    }
  }
  echanger(T[fin], T[j]);
  return j;
}
*/
/* Tri Rapide */
void triRapInd1(int* T, size_t deb, size_t fin)
/* trie le sous-tableau T[g..d] selon le tri rapide */
{
  /*
  if(deb < fin){
    int p = pivot(T, deb, fin);
    triRapInd1(T, deb, p-1);
    triRapInd1(T, p+1, fin);
    }
  */
  return;
}

void triRapide1(int* T, size_t taille)
{
  triRapInd1(T,0,taille-1);
  return;
}

/*
int* fusion(int* T1, int* T2){

  if(T1 == NULL){
    return T2;
  }
  if(T2 == NULL){
    return T1;
  }

  if(T1[1] <= T2[1]){
    return copy(T1[1], fusion(T1+1, T2));
  }
  else{
    return copy(T2[1], fusion(T1, T2+1));
  }
  
  return NULL;
}
*/
/* tri par Fusion */
void triFusionBis(int* T, size_t g, size_t d)
/* trie le sous-tableau T[g..d] par fusion */
{
  /*
  if(d <= 1){
    return;
  }
  else{
    fusion(triFusionBis(T, g, (g+d)/2), triFusionBis(T, (g+d)/2, d));
  }
  */
}
void triFusion(int* T, size_t taille)
{
  triFusionBis(T,0,taille-1);
  return;
}
 
/* Nombre de valeurs différentes dans un tableau */
int nbValDiff(int T[], size_t taille)
// Complexité : ?????
{
  int k =0;
  unsigned int n=0;
  int comparateur = 0;
  if(n == taille){
    return k;
  }
  if(n+1 == taille){
    return k+1;
  }
  int j=0;
  comparateur = T[0];
  triRapide1(T, taille);
  for (unsigned int i=0; i < taille; i++){
    if(comparateur != T[i]){
      j++;
      comparateur = T[i];
    }
  }
  return j;
}
