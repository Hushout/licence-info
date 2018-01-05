#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include "Affichage.h"
#include "array_functions.h"

using namespace std;

void generate_vertices(int ** , int);
void generate_neighbors(int ** , int , int , vector<int> *);
void djikstra(int ** , vector<int> * ,  int * , int * , int);
void generate_djikstra_tree(int ** , int * , int);
int distance(int ** ,  int , int);
bool are_neighbors(vector<int> * , int , int);
bool exists_non_visited_vertex(bool * , int);
int vertex_closest_to_root(int * , bool * , int);
int tree_size(int * , int);

int main(int argc , char * argv[]){
    
    //############################## VARIABLES ####################################
    srand((u_int)time(NULL));
    int nb_vertices;                        //Le nombre de points.
    int nb_edges;                           //Le nombre d aretes.
    int max_distance;                       //La distance jusqu'a laquelle on relie deux points.
    
    if(argc > 1) {
        char * p;
        nb_vertices = (int)strtol(argv[1], &p, 10);
    } else {
        cout << "Set the number of vertices ";
        cin >> nb_vertices;
    }
    
    if(argc > 2) {
        char * p;
        max_distance = (int)strtol(argv[2], &p, 10);
    } else {
        cout << "Set the maximum length for the edges : ";
        cin >> max_distance;
    }
    max_distance *= max_distance;
    
    vector<int> * neighbors = new vector<int> [nb_vertices];        // Les listes de voisins.
    int ** vertices = new int * [nb_vertices];                      // Les coordonnees des points.
    int ** tree;                                                    // Les aretes de l'arbre de Dijkstra.
    int * distance_to_root = new int [nb_vertices];                 // La distance a la racine.
    int * parent = new int [nb_vertices];                           // La relation de filiation de l'arbre de Dijkstra.
    for(int i = 0 ; i < nb_vertices ; i++) vertices[i] = new int [2];
    //########################################################################
    
    
    //########################### MAIN PROGRAM ###############################
    cout << "Generating vertices" << endl;
    generate_vertices(vertices, nb_vertices);
    cout << "Sorting vertices" << endl;
    complete_merge_sort(vertices , nb_vertices , 2);
    cout << "####################### GRAPH ######################" << endl;
    print_vertices(vertices, nb_vertices);
    cout << "####################################################" << endl << endl;
    
    cout << "Generating edges" << endl;
    generate_neighbors(vertices, nb_vertices, max_distance, neighbors);
    cout << "####################### GRAPH ######################" << endl;
    print_graph(neighbors , nb_vertices);
    cout << "####################################################" << endl << endl;
    
    cout << "Writing graph to file" << endl;
    AffichageGraphique(vertices , neighbors , nb_vertices , "graph");
    
    cout << "Running Djikstra algorithm on the graph" << endl;
    djikstra(vertices, neighbors, parent, distance_to_root, nb_vertices);
    nb_edges = tree_size(parent, nb_vertices);
    tree = new int * [nb_edges];
    for(int i = 0 ; i < nb_edges ; i++) tree[i] = new int [2];
    cout << "Generating Djikstra tree" << endl;
    generate_djikstra_tree(tree, parent, nb_vertices);
    cout << "################### DJIKSTRA TREE ##################" << endl;
    print_tree(tree , nb_edges);
    cout << "####################################################" << endl << endl;
    
    
    cout << "Writing tree to file" << endl;
    AffichageGraphique(tree , vertices , parent , nb_vertices , nb_edges , "djikstra");
    //########################################################################

    
    //####################### FREEING MEMORY #################################
    for(int i = 0 ; i < nb_vertices - 1 ; i++) delete [] vertices[i];
    for(int i = 0 ; i < nb_edges ; i++) delete [] tree[i];
    delete [] vertices[nb_vertices - 1];
    delete [] vertices;
    delete [] tree;
    delete [] distance_to_root;
    delete [] parent;
    delete [] neighbors;
    //########################################################################

    return 0;
}

void generate_vertices(int ** vertices , int nb_vertices) {
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        vertices[i][0] = rand() % 612;
        vertices[i][1] = rand() % 792;
    }
}

void generate_neighbors(int ** vertices , int nb_vertices , int max_distance , vector<int> * neighbors) {

    for(int i = 0 ; i < nb_vertices ; i++) {
        
        for(int j = 0 ; j < nb_vertices ; j++) {
            
            if(i != j && !are_neighbors(neighbors , i , j)) {
                
                if (distance(vertices , i , j) <= max_distance) {
                    neighbors[i].push_back(j);
                    neighbors[j].push_back(i);
                } else {
                    //cout << i << " and " << j << " too far apart : " << distance << endl;
                }
            }
        }
    }
}

void djikstra(int ** vertices , vector<int> * neighbors ,  int * parent , int * distance_to_root , int nb_vertices) {
    bool * visited_vertices = new bool [nb_vertices];
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        visited_vertices[i] = false;
        distance_to_root[i] = pow(612 , 2) + pow(792 , 2);
        parent[i] = -1;
    }
    parent[0] = 0;
    distance_to_root[0] = 0;
    //visited_vertices[0] = true;
    
    while(exists_non_visited_vertex(visited_vertices , nb_vertices)) {
        int current_vertex = vertex_closest_to_root(distance_to_root , visited_vertices , nb_vertices);
        //cout << "Processing " << current_vertex << endl;
        visited_vertices[current_vertex] = true;
        
        for(int i = 0 ; i < neighbors[current_vertex].size() ; i++) {
            int dx = distance_to_root[current_vertex],
            dy = distance_to_root[neighbors[current_vertex][i]],
            lxy = distance(vertices , current_vertex , neighbors[current_vertex][i]);
            
            if(!(visited_vertices[neighbors[current_vertex][i]]) && dy > dx + lxy) {
                distance_to_root[neighbors[current_vertex][i]] = dx + lxy;
                parent[neighbors[current_vertex][i]] = current_vertex;
                //cout << dx << " | " << dy << " : " << lxy << endl;
            }
        }
    }
}

void generate_djikstra_tree(int ** tree , int * parent , int nb_vertices) {
    int current_index = 0;
    
    for(int i = 1 ; i < nb_vertices ; i++) {
        
        if(parent[i] != -1) {
            tree[current_index][0] = parent[i];
            tree[current_index][1] = i;
            current_index++;
        }
    }
}

bool are_neighbors(vector<int> * neighbors , int origin_vertex , int end_vertex) {
    
    for(int i = 0 ; i < neighbors[origin_vertex].size() ; i++) {
        
        if(neighbors[origin_vertex][i] == end_vertex)
            return true;
    }
    return false;
}

int distance(int ** vertices , int origin_vertex , int end_vertex) {
    return pow(vertices[end_vertex][0] - vertices[origin_vertex][0] , 2) + pow(vertices[end_vertex][1] - vertices[origin_vertex][1] , 2);
}

bool exists_non_visited_vertex(bool * visited_vertices , int nb_vertices) {
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        
        if(!(visited_vertices[i]))
            return true;
    }
    return false;
}

int vertex_closest_to_root(int * distance_to_root , bool * visited_vertices , int nb_vertices) {
    int current_choice = -1,
    i = 0;
    
    while(current_choice == -1) {
        
        if(!visited_vertices[i])
            current_choice = i;
        i++;
    }
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        
        if(!visited_vertices[i] && distance_to_root[i] < distance_to_root[current_choice])
            current_choice = i ;
    }
    return current_choice;
}

int tree_size(int * parent , int nb_vertices) {
    int return_value = -1;
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        
        if(parent[i] != -1) return_value++;
    }
    return return_value;
}