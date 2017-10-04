#include <iostream>
#include <vector>

using namespace std;

const int n=5;
const int inf=9999;                    //La valeur infinie.    

int main(){

  int longueur[n][n]={{0,2,inf,4,inf}, //Les longueurs des arcs.
                  {inf,0,2,inf,inf},   //long[i][j]=inf si l'arc ij n'existe pas
                  {inf,inf,0,2,inf},
                  {inf,-3,inf,0,2},
                  {2,inf,inf,inf,0}};                
  int dist[n][n];                      //Le tableau des distances.
  int chemin[n][n];                    //Le tableau de la premiere etape du chemin de i a j.

return 0;
}


/* Pour le calcul de la fermeture transitive:

const int n=6;
int arc[n][n]={{0,0,0,1,0,1},//La matrice d'adjacence du graphe oriente D.
               {1,0,1,1,0,0},
               {0,0,0,1,0,0},
               {0,0,0,0,1,1},
               {0,0,1,0,0,1},
               {0,0,1,0,0,0}};                
int fermeture[n][n];         // La matrice de la fermeture transitive de D.

*/
