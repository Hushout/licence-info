#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include <vector>
typedef struct coord{int abs; int ord;} coord;
void AffichageGraphique(int n, coord point[], int arbre[][2]);
void AffichageGraphiqueVoisins(int n, coord point[], std::vector<int> voisins[]);
void AffichageGraphiqueParcours(int n, coord point[], int pere[]);
#endif
