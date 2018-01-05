#include "Arbo.h"

////// Odorico Thibault //////

/******* Liste chainee Début *******/

Cellule::Cellule (Arbo A){
  fils = A;
  Apres = NULL;
}

ListeCellules Cellule::EstDansListeP(Arbo A){
  if (fils == A) return this;
  if (Apres == NULL) return NULL;
  return Apres->EstDansListeP(A);
}

ListeCellules Cellule::AjouterSuccesseur(Arbo A){
  if (!EstDansListeP(A)) {
    ListeCellules ptCell = new Cellule(A);
    ptCell->Apres = this;
    return ptCell;
  }
  return this;
}

ListeCellules Cellule::RetirerSuccesseur(Arbo A){
  if (fils == A) return Apres;
  if (!Apres) return this;
  Apres = Apres->RetirerSuccesseur(A); 
  return this;
}

/******* Liste chainee Fin *******/


/************Arborescence Debut*************/

Sommet::Sommet(Valeur v){
  racine = v;
  ListeSuccesseurs = NULL;
}

ListeCellules Sommet::EstSuccesseurP(Arbo A){
  if (ListeSuccesseurs) return ListeSuccesseurs->EstDansListeP(A);
  return NULL;
}

void Sommet::AjouterSuccesseur(Arbo A){
  if (!ListeSuccesseurs){
    ListeSuccesseurs=new Cellule(A);
    return;
  }
  if (!ListeSuccesseurs->EstDansListeP(A)) {
    ListeSuccesseurs = ListeSuccesseurs->AjouterSuccesseur(A);
  }
  return;
}

void Sommet::RetirerSuccesseur(Arbo A){
  if (ListeSuccesseurs && ListeSuccesseurs->EstDansListeP(A)) {
    ListeSuccesseurs = ListeSuccesseurs->RetirerSuccesseur(A);
  }
  return;
}

ostream& operator<<(ostream& os, Sommet& S){
  os<< S.racine <<" ";
  return os;
}

/************Arborescence Fin*************/

/************Traversee recursive Debut*************/

void TraverseePrefixeRec(Arbo A){
  if(!A) {
    cout << endl; 
    return;
  }
  
  cout<< *A <<" ";
  
  for (ListeCellules L = A->ListeSuccesseurs ; L != NULL ; L = L->Apres){
    TraverseePrefixeRec(L->fils);
  }
  return;
}

/************Traversee recursive Fin*************/

/**********Pile Début*********/

Pile::Pile(){
  Sommet = NULL;
}

bool Pile::VideP(){
  return Sommet == NULL;
}


void Pile::Empiler(Arbo A){
  ListeCellules ptCellule = new Cellule(A);
  ptCellule->Apres = Sommet;
  Sommet = ptCellule;
  return;
}


Arbo Pile::Depiler(){
  ListeCellules ptCellule = Sommet;
  Sommet = Sommet->Apres;
  return ptCellule->fils;
}

/**********Pile Fin*********/

/************Traversee  prefixe iterative Debut*************/

void TraverseePrefixeIt(Arbo A){
  Pile* P = new Pile;
  Pile* PTemp = new Pile;
  
  P->Empiler(A);
  
  while(!P->VideP()){
    
    Arbo B = P->Depiler();
    cout << *B << " ";
	
    for (ListeCellules L = B->ListeSuccesseurs ; L != NULL ; L = L->Apres){
      PTemp->Empiler(L->fils);
    }

    while(!PTemp->VideP()){
      P->Empiler(PTemp->Depiler());
    }
  }
}

/************Traversee  prefixe iterative Fin*************/


/**********File Début*********/

File::File(){
  Sortie = NULL;
  Entree = NULL;
}


bool File::VideP(){
  return Sortie == NULL;
}


void File::Enfiler(Arbo A){
  ListeCellules ptCellule = new Cellule(A);
  if (Entree) Entree->Apres = ptCellule;
  Entree = ptCellule;
  if (!Sortie) Sortie = ptCellule;
  return;
}


Arbo File::Defiler(){
  ListeCellules ptCellule = Sortie;
  Sortie = Sortie->Apres;
  return ptCellule->fils;
}

/**********File Fin*********/

/************Traversee Largeur Debut*************/

void TraverseeLargeur(Arbo A){
  File* F = new File;
  F->Enfiler(A);
  
  while(!F->VideP()){
	Arbo B = F->Defiler();
  	cout << *B << " ";
	
	for (ListeCellules L = B->ListeSuccesseurs ; L != NULL ; L = L->Apres){
	  F->Enfiler(L->fils);
	}
  }
}

/************Traversee Largeur Fin*************/

int main(){


  Arbo A0 = new Sommet(0);
  Arbo A1 = new Sommet(1);
  Arbo A2 = new Sommet(2);
  Arbo A3 = new Sommet(3);
  Arbo A4 = new Sommet(4);
  Arbo A5 = new Sommet(5);
  Arbo A6 = new Sommet(6);

  A3->AjouterSuccesseur(A6);
  A1->AjouterSuccesseur(A5);
  A3->AjouterSuccesseur(A4);
  A2->AjouterSuccesseur(A3);
  A0->AjouterSuccesseur(A2);
  A0->AjouterSuccesseur(A1);
  
  
/*
Representation de l'arboressence construite:

                    A0
                   /  \
                  A1  A2
                  |    |
                  A5   A3
                      /  \
                     A4  A6
*/
  

  cout << "rec A0  ";
  TraverseePrefixeRec(A0);
  cout << endl;

  cout << "iter A0  ";
  TraverseePrefixeIt(A0);
  cout << endl;

  cout << "largeur  ";
  TraverseeLargeur(A0);
  cout << endl << endl;

  //Changemement de A5 par A6 pour voir si RetirerSuccesseur fonctionne
  
  A3->RetirerSuccesseur(A6);
  A3->RetirerSuccesseur(A2);

  cout << "rec A0 apres retrait A6 ";
  TraverseePrefixeRec(A0);
  cout << endl;
  
  cout << "iter A0 apres retrait A6 ";
  TraverseePrefixeIt(A0);
  cout << endl;
  
  return 1;
}
