#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include "Affichage.h"

using namespace std;


          
void AffichageGraphique(int n, coord point[], int arbre[][2])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("Exemple.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;  
 for(int i=0;i<n;i++)
   {output << point[i].abs << " " << point[i].ord << " 3 0 360 arc" <<endl;
   output << "0 setgray" <<endl;
   output << "fill" <<endl;
   output << "stroke"<<endl;
   output << endl;
   }
 output << endl;
 for(int i=0;i<n-1;i++)
   {output << point[arbre[i][0]].abs << " " << point[arbre[i][0]].ord 
	   << " moveto" << endl;
   output << point[arbre[i][1]].abs << " " << point[arbre[i][1]].ord
	  << " lineto" << endl;
   output << "stroke" << endl;
   output << endl;
   }
 output << "showpage";
 output << endl;
}


void AffichageGraphiqueVoisins(int n, coord point[], vector<int> voisins[])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("Voisins.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;  
 for(int i=0;i<n;i++)
   {output << point[i].abs << " " << point[i].ord << " 1 0 360 arc" <<endl;
   output << "0 setgray" <<endl;
   output << "fill" <<endl;
   output << "stroke"<<endl;
   output << endl;
   }
 output << endl;
 for(int i=0;i<n;i++)
   {
	   for(int j = 0 ; j < (int)voisins[i].size() ; j++){
		   	  
			output << point[i].abs << " " << point[i].ord 
			<< " moveto" << endl;
			output << point[voisins[i][j]].abs << " " << point[voisins[i][j]].ord
			<< " lineto" << endl;
			output << "stroke" << endl;
			output << endl;
	   }
   }
 output << "showpage";
 output << endl;
}

void AffichageGraphiqueParcours(int n, coord point[], int pere[])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("Parcours.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;  
 for(int i=0;i<n;i++)
   {output << point[i].abs << " " << point[i].ord << " 1 0 360 arc" <<endl;
   output << "0 setgray" <<endl;
   output << "fill" <<endl;
   output << "stroke"<<endl;
   output << endl;
   }
 output << endl;
 for(int i=0;i<n;i++)
   {
		if(pere[i] != -1){
			output << point[i].abs << " " << point[i].ord 
			<< " moveto" << endl;
			output << point[pere[i]].abs << " " << point[pere[i]].ord
			<< " lineto" << endl;
			output << "stroke" << endl;
			output << endl;
	   }
   }
 output << "showpage";
 output << endl;
}