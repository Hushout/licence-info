#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <fstream>
#include "array_functions.h"
#include "Affichage.h"

using namespace std;

void generate_vertices(int ** , int);
void distances(int ** , int , int ** , int);
void kruskal(int ** , int , int , int **);
void kruskal_opti(int ** , int , int , int **);
void travelling_salesman(int ** , int ** , int , int , int);

int main(int argc , char * argv[]){
    srand((u_int)time(NULL));
    clock_t t;
    int nb_vertices;
    
    if(argc < 2) {
        cout << "Entrer le nombre de points: ";
        cin >> nb_vertices;
        
    } else {
        char *p;
        nb_vertices = (int)strtol(argv[1] , &p , 10);
    }
    
    int nb_edges = nb_vertices * (nb_vertices - 1) / 2,
    optimal_path_length = 0,
    recursion_counter;
    int ** vertices = new int * [nb_vertices];
    int ** edges = new int * [nb_edges];
    int ** tree = new int * [nb_vertices - 1];
    int ** tour_graph = new int * [nb_vertices - 1];
    
    for(int i = 0 ; i < nb_vertices - 1 ; i++) {
        tour_graph[i] = new int [2];
    }
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        vertices[i] = new int [2];
        vertices[i][0] = 0;
        vertices[i][1] = 0;
    }
    
    for(int i = 0 ; i < nb_edges ; i++) {
        edges[i] = new int [3];
        edges[i][0] = 0;
        edges[i][1] = 0;
        edges[i][2] = 0;
    }
    
    for(int i = 0 ; i < nb_vertices - 1 ; i++) {
        tree[i] = new int [2];
        tree[i][0] = 0;
        tree[i][1] = 0;
    }
    
    generate_vertices(vertices, nb_vertices);
    complete_merge_sort(vertices, nb_vertices , 2);
    cout << "################ VERTICES ################" << endl;
    print_vertices(vertices , nb_vertices);
    cout << "##########################################" << endl << endl;
    
    distances(vertices , nb_vertices , edges , nb_edges);
    merge_sort(edges , 0 , nb_edges, 3 , 2);
    cout << "############### DISTANCES ################" << endl;
    print_distances(edges , nb_edges);
    cout << "##########################################" << endl << endl;
    
    cout << "Calculating Kruskal tree with the standard algorithm" << endl;
    t = clock();
    kruskal(edges, nb_vertices, nb_edges, tree);
    clock_t t1 = clock() - t;
    
    for(int i = 0 ; i < nb_vertices - 1 ; i++) {
        tree[i][0] = 0;
        tree[i][1] = 0;
    }
    
    cout << "Calculating Kruskal tree with the optimised algorithm" << endl;
    t = clock();
    kruskal_opti(edges, nb_vertices, nb_edges, tree);
    clock_t t2 = clock() - t;
    AffichageGraphique(vertices , tree , nb_vertices , "kruskal");
    cout << "Standard algorithm took " << (float)t1/CLOCKS_PER_SEC << "s" << endl;
    cout << "Optimised algorithm took " << (float)t2/CLOCKS_PER_SEC << "s" << endl << endl;
    
    cout << "############### KRUSKAL TREE ###############" << endl;
    cout << "###### SORTED BY SHORTEST EDGES FIRST ######" << endl;
    print_graph(tree, nb_vertices - 1);
    cout << "############################################" << endl << endl;
    
    if(argc < 3) {
        cout << "How many times should we loop the algorithm? ";
        cin >> recursion_counter;
        
    } else {
        char *p;
        recursion_counter = (int)strtol(argv[2] , &p , 10);
    }
    cout << "Calculating an optimal tour through the tree" << endl;
    travelling_salesman(edges , tree , recursion_counter , nb_vertices , nb_edges);
    cout << "Done" << endl;
    AffichageGraphique(vertices , tree , nb_vertices, "tour_by_shortest_edges");
    cout << "############### OPTIMAL TOUR ###############" << endl;
    for(int i = 0 ; i < nb_vertices - 1; i++) {
        cout << tree[i][0] << " -> " << tree[i][1] << endl;
        optimal_path_length += pow(vertices[tree[i][1]][0] - vertices[tree[i][0]][0] , 2) + pow(vertices[tree[i][1]][1] - vertices[tree[i][0]][1] , 2);
        
    }
    cout << endl << "Total distance : " << optimal_path_length << endl;
    cout << "############################################" << endl << endl;
    optimal_path_length = 0;
        for(int i = 0 ; i < nb_vertices ; i++) {
        delete [] vertices[i];
    }
    
    for(int i = 0 ; i < nb_edges ; i++) {
        delete [] edges[i];
    }
    
    for(int i = 0 ; i < nb_vertices - 1 ; i++) {
        delete [] tour_graph[i];
        delete [] tree[i];
    }
    
    delete [] vertices;
    delete [] edges;
    delete [] tree;
    return 0;
}

void generate_vertices(int ** vertices , int nb_vertices) {
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        
        vertices[i][0] = rand() % 612;
        vertices[i][1] = rand() % 792;
    }
}

void distances(int ** vertices , int nb_vertices , int ** edges , int nb_edges) {
    int vertical_distance,
    horizontal_distance,
    k = 0;
    
    for(int i = 0 ; i < nb_vertices - 1 ; i++) {
        
        for(int j = i + 1 ; j < nb_vertices ; j++) {
            edges[k][0] = i;
            edges[k][1] = j;
            horizontal_distance = vertices[j][0];
            horizontal_distance -= vertices[i][0];
            vertical_distance = vertices[j][1];
            vertical_distance -= vertices[i][1];
            edges[k][2] = pow(horizontal_distance , 2) + pow(vertical_distance , 2);
            k++;
        }
    }
}

void kruskal(int ** edges , int nb_vertices , int nb_edges , int ** tree) {
    int * comp = new int [nb_vertices],
    top = 0;
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        comp[i] = i;
    }
    
    for(int i = 0 ; i < nb_edges ; i++) {
        
        if(comp[edges[i][0]] != comp[edges[i][1]]) {
            int aux = comp[edges[i][0]];
            tree[top][0] = edges[i][0];
            tree[top][1] = edges[i][1];
            top++;
            
            for(int k = 0 ; k < nb_vertices ; k++) {
                
                if(comp[k] == aux) {
                    comp[k] = comp[edges[i][1]];
                }
            }
        }
    }
}

void kruskal_opti(int ** edges , int nb_vertices , int nb_edges , int ** tree) {
    int * comp = new int [nb_edges],
    top = 0;
    
    vector< vector<int> >  components (nb_vertices , vector<int> (0));
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        components[i].push_back(i);
        comp[i] = i;
    }
    
    for(int i = 0 ; i < nb_edges ; i++) {
        
        if(comp[edges[i][0]] != comp[edges[i][1]]) {
            int comp_begin = comp[edges[i][0]],
            comp_end = comp[edges[i][1]];
            
            if(components[comp_begin].size() > components[comp_end].size()) {
                comp_begin = comp[edges[i][1]],
                comp_end = comp[edges[i][0]];
            }
            int size = (int)components[comp_begin].size();
            tree[top][0] = edges[i][0];
            tree[top][1] = edges[i][1];
            top++;
            
            for(int j = 0 ; j < size ; j++) {
                int t = components[comp_begin].back();
                components[comp_begin].pop_back();
                components[comp_end].push_back(t);
                comp[t] = components[comp_end][0];
            }
        }
    }
}

void travelling_salesman(int ** edges , int ** tree , int recursion_counter , int nb_vertices , int nb_edges) {
    if(recursion_counter > 0) {
        int * optimal_tour = new int [nb_vertices];
        vector<int *> branching_queue,
        return_queue;
        int current_vertex = tree[0][0],
        return_queue_index = 0,
        visited_vertices_index = 1;
        
        optimal_tour[0] = current_vertex;
        
        for(int i = 0 ; i < nb_vertices - 1 ; i++) {
            
            if(current_vertex == tree[i][1]) {
                int temp = tree[i][1];
                tree[i][1] = tree[i][0];
                tree[i][1] = temp;
            }
            
            if(current_vertex == tree[i][0]) {
                return_queue.push_back(new int [2]);
                return_queue[return_queue_index][0] = current_vertex;
                current_vertex = tree[i][1];
                return_queue[return_queue_index][1] = current_vertex;
                optimal_tour[visited_vertices_index] = current_vertex;
                return_queue_index++;
                visited_vertices_index++;
                
            } else {
                int branching_queue_size = (int)branching_queue.size();
                branching_queue.push_back(new int [2]);
                branching_queue[branching_queue_size][0] = tree[i][0];
                branching_queue[branching_queue_size][1] = tree[i][1];
            }
        }
        
        while(visited_vertices_index < nb_vertices && branching_queue.size() > 0) {
            int i = 0;
            
            while(i < branching_queue.size() && i > -1) {
                
                if(current_vertex == branching_queue[i][1]) {
                    int temp = branching_queue[i][1];
                    branching_queue[i][1] = branching_queue[i][0];
                    branching_queue[i][0] = temp;
                }
                
                if(current_vertex == branching_queue[i][0]) {
                    return_queue.push_back(new int [2]);
                    return_queue[return_queue_index][0] = current_vertex;
                    current_vertex = branching_queue[i][1];
                    return_queue[return_queue_index][1] = current_vertex;
                    optimal_tour[visited_vertices_index] = current_vertex;
                    delete [] branching_queue[i];
                    branching_queue.erase(branching_queue.begin() + i);
                    return_queue_index++;
                    i = -1;
                    visited_vertices_index++;
                    
                } else {
                    i++;
                }
            }
            
            if(i == branching_queue.size()) {
                return_queue_index--;
                current_vertex = return_queue[return_queue_index][0];
                return_queue.pop_back();
            }
        }
        
        for(int i = 0 ; i < nb_vertices - 1; i++) {
            tree[i][0] = optimal_tour[i];
            tree[i][1] = optimal_tour[i + 1];
        }
        
        travelling_salesman(edges, tree, recursion_counter - 1 , nb_vertices, nb_edges);
    }
}