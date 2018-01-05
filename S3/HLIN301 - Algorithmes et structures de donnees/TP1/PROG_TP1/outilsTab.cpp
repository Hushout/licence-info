#include <iostream>
#include <fstream>

#include <stdlib.h>  // pour rand
#include <assert.h>
#include "outilsTab.h"
using namespace std;
 
int* genTab(int n){
    int* t; int i;
    t=new int[n];
    for (i=0;i<n;i++) t[i]=-100+rand()%200;
    return t;
}

void afficheTab(int* T, int taille){
    int i;
    cout << "\n[ ";
    for (i=0;i<taille;i++) cout << T[i] << " ";
    cout << "]\n";
    }

void fichierTemps(const char* nomFic, int tMaxTab, int pas, int (*f)(int*, int)){
    int taille;
    int* Tab;
    clock_t t1, t2;    
    ofstream fichier(nomFic,ios::out);

    if (fichier)
    {
        for (taille=pas; taille<=tMaxTab; taille=taille+pas){
            Tab=genTab(taille);
            t1=clock();
            (*f)(Tab,taille);
            t2=clock();
            fichier << taille <<" "<< (double)(t2-t1)/ CLOCKS_PER_SEC << endl;
        }
        fichier.close();
    }
    else cerr << " Problème ouverture fichier"<< endl;

    return ;
}

int ssTabSomMax1(int* T, int taille){
    int somMax, som, i, j, k;
    somMax=0;
    for (i=0;i<taille;i++){
        for (j=i; j<taille; j++){
            som=0;
            for (k=i; k<=j; k++) {
                som = som + T[k];
            }
            if (som > somMax) somMax = som;
        }
    }
    return somMax;
}

int ssTabSomMax2(int* T, int taille){
    int somMax, som, i, j;
    somMax=0;
    for (i=0;i<taille;i++){
        som=0;
        for (j=i; j<taille; j++){
            som = som + T[j];
            if (som > somMax) somMax = som;
        }
    }
    return somMax;
}

int sTSM3(int* T,int g,int d){
    int m, som, i, smgd, smdg, smm, smg, smd;
    assert(g<=d);
    if (g==d){
        if (T[g]>0) return T[g]; else return 0;
    }
    else {
        m = (d+g)/2;
        smg=sTSM3(T,g,m);
        smd=sTSM3(T,m+1,d);
        smgd=0; som=0;
        for (i=m;i>=g;i--){
            som=som+T[i];
            if (som > smgd) smgd=som;
        }
        smdg=0; som=0;
        for(i=m+1;i<=d;i++){
            som=som+T[i];
            if (som>smdg) smdg=som;
        }
        smm=smgd+smdg;
        if ((smg>=smd) && (smg>=smm)) return smg;
        else {
            if (smd>=smm) return smd;
            else return smm;
        }
    }
}

int ssTabSomMax3(int* T, int taille){
    return sTSM3(T,0,taille-1);
}

int ssTabSomMax4(int* T, int taille){
  int somMax = 0;
  int somMaxDroite = 0;
  for(int i = 0 ; i < taille ; i++){
    somMaxDroite = max(0, T[i] + somMaxDroite);
    somMax = max(somMax, somMaxDroite);
  }
  return somMax;
}

struct triplet indSsTabSomMax(int* T, int taille){

  struct triplet  res;
  res.somMax = 0; res.deb = 0; res.fin = 0;
  
  int somMaxDroite = 0;
  
  for(int i = 0 ; i < taille ; i++){
    somMaxDroite = max(0, T[i] + somMaxDroite);
    res.somMax = max(res.somMax, somMaxDroite);
    
    if(res.somMax == somMaxDroite){
      res.deb = i;
    }
    
    if(res.somMax > somMaxDroite){
      res.fin = i;
    }
  }
   
  return res;
}


void rangerElemNeg(int* T,int taille){
  
  int tmp;
  
  for(int j = 0 ; j < taille ; j++){
    for(int i = 0 ; i < taille ; i++){
      
      if(T[i] >= 0){
	tmp = T[i+1];
	T[i+1] = T[i];
	T[i] = tmp;
      }
      
    }
  }
   return;
}
