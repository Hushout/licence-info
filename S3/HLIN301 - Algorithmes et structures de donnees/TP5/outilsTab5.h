#ifndef OUTILSTAB_H_INCLUDED
#define OUTILSTAB_H_INCLUDED

int* copieTab(int *T, size_t t);
/*
  Renvoie une copie du tableau T de taille t
 */

int* genTab(size_t t);
/*
    Renvoie un tableau de taille t, dont les éléments sont des entiers aléatoires 
*/

void afficheTab(int* T, size_t t);
/*
    Affiche les éléments de T, tableau d'entiers de taille t
*/
 
void fichierTemps(const char * nomFic, size_t tMaxTab, size_t pasTaille, void (*fTri)(int*,size_t));
/*
    Données  : nomFic : nom d'un fichier,
               tMaxTab et pasTaille 2 entiers positifs pasTaille < tMaxTab
	       fTri nom d'une fonction de tri d'un tableau d'entiers de taille donnée
    Resultat : crée un fichier de nom nomfic 
            et pour chaque taille comprise entre pasTaille et tMaxTab (avec un pas de pasTaille),
            génère un tableau de cette taille
            execute la fonction Tri sur ce tableau
            ajoute au fichier de nom nomfic la taille du tableau et le temps d'execution du tir
*/


void triInsertion(int* T, size_t taille);
/* tri le tableau T contenant taille entiers avec l'algorithme de tri par insertion */

void triSelection(int* T, size_t taille);
/* tri le tableau T contenant taille entiers avec l'algorithme de tri par sélection */

void triFusion(int* T, size_t taille);
/* tri le tableau T contenant taille entiers avec l'algorithme de tri par fusion */

void triParTas(int* T, size_t taille);
/* tri le tableau T contenant taille entiers avec l'algorithme de tri par tas */

int pivot(int* T, size_t deb, size_t fin);

void triRapide1(int* T, size_t taille);
/* tri le tableau T contenant taille entiers avec l'algorithme de tri rapide */




int nbValDiff(int* T, size_t taille); 
/* renvoie le nombre de valeurs différentes des taille éléments du tableau T */

#endif /* OUTILSTAB_H_INCLUDED */ 
