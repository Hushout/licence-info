#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void AffichageGraphique(int ** vertices, int ** tree, int nb_vertices , int nb_edges , string file_name) {    // Cree le fichier Exemple.ps qui affiche
    // les points et l'arbre de Kruskal.
    ofstream output;
    output.open(file_name + ".ps" , ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << "%%BoundingBox: 0 0 612 792" << endl;
    output << endl;
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        output << vertices[i][0] << " " << vertices[i][1] << " 3 0 360 arc" << endl;
        output << "0 setgray" << endl;
        output << "fill" << endl;
        output << "stroke"<< endl;
        output << endl;
    }
    output << endl;
    
    for(int i = 0 ; i < nb_edges ; i++) {
        output << vertices[tree[i][0]][0] << " " << vertices[tree[i][0]][1]
        << " moveto" << endl;
        output << vertices[tree[i][1]][0] << " " << vertices[tree[i][1]][1]
        << " lineto" << endl;
        output << "stroke" << endl;
        output << endl;
    }
    output << "showpage";
    output << endl;
}

void AffichageGraphique(int ** vertices , vector<int> * neighbors, int nb_vertices , string file_name) {
    ofstream output;
    output.open(file_name + ".ps" , ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << "%%BoundingBox: 0 0 612 792" << endl;
    output << endl;
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        output << vertices[i][0] << " " << vertices[i][1] << " 3 0 360 arc" << endl;
        output << "0 setgray" << endl;
        output << "fill" << endl;
        output << "stroke"<< endl;
        output << endl;
    }
    output << endl;
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        
        for(int j = 0 ; j < neighbors[i].size() ; j++) {
            
            if(i < neighbors[i][j]) {
                output << vertices[i][0] << " " << vertices[i][1]
                << " moveto" << endl;
                output << vertices[neighbors[i][j]][0] << " " << vertices[neighbors[i][j]][1]
                << " lineto" << endl;
                output << "stroke" << endl;
                output << endl;
            }
        }
    }
    output << "showpage";
    output << endl;
}
