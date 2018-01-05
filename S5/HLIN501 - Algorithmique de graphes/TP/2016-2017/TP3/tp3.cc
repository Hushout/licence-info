#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>
#include "Affichage.h"
#include "array_functions.h"

using namespace std;

void generate_vertices(int ** , int);
void generate_random_graph(int ** , vector<int> * , int , int * , int);
void horizontal_traversal(vector<int> * , int * , int * , int * , int);
void depth_first_traversal(vector<int> * , int * , int * , int * , int);
bool are_linked(vector<int> * , vector<int> * , int , int);
int nb_useful_vertices(int * , int);
int distance(int ** , int , int);


int main(int argc , char * argv[]){
    //################################### DECLARATIONS AND INITIALIZATIONS ################################################
    srand((u_int)time(NULL));
    int nb_vertices = 0;
    int nb_edges = 0;
    int nb_tree_edges = 0;
    int max_distance = 0;
    
    if(argc > 1) {
        char * p;
        nb_vertices = (int)strtol(argv[1] , &p , 10);
    } else {
        cout << "Entrer the number of vertices : ";
        cin >> nb_vertices;
    }
    if(argc > 2) {
        char * p;
        nb_edges = (int)strtol(argv[2] , &p , 10);
    } else {
        cout << "Enter the number of edges (0 to " << nb_vertices - 1 << ") : ";
        cin >> nb_edges;
    }
    if(argc > 3) {
        char * p;
        max_distance = (int)strtol(argv[3] , &p , 10);
    } else {
        cout << "Enter the number of edges : ";
        cin >> max_distance;
    }
    max_distance *= max_distance;
    vector<int> * neighbors = new vector<int> [nb_vertices];
    int ** tree;
    int ** vertices = new int * [nb_vertices];
    int * parent = new int [nb_vertices];
    int * parsing_order = new int [nb_vertices];
    int * depth = new int [nb_vertices];
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        vertices[i] = new int [2];
        depth[i] = -1;
        parsing_order[i] = -1;
        parent[i] = -1;
    }
    parsing_order[0] = 1;
    depth[0] = 0;
    parent[0] = 0;
    //##############################################################################################
    
    //############################# MAIN PROGRAM ###################################################
    cout << "Generating random graph" << endl;
    generate_vertices(vertices, nb_vertices);
    complete_merge_sort(vertices , nb_vertices , 2);
    generate_random_graph(vertices , neighbors, nb_vertices, &nb_edges , max_distance);
    cout << "############################# GRAPH #############################" << endl;
    print_graph(neighbors, nb_vertices);
    cout << "################################################################" << endl << endl;
    AffichageGraphique(vertices, neighbors, nb_vertices, "graph");
    
    cout << "Performing horizontal traversal of the tree" << endl;
    horizontal_traversal(neighbors, depth, parsing_order, parent, nb_vertices);
    nb_tree_edges = nb_useful_vertices(parent , nb_vertices) - 1;
    tree = new int * [nb_tree_edges];
    for(int i = 0 ; i < nb_tree_edges ; i++) tree[i] = new int [2];
    convert_to_edges(tree , parsing_order , parent , nb_vertices);
    cout << "######################## TRAVERSED TREE ########################" << endl;
    print_tree(tree , nb_tree_edges);
    cout << "################################################################" << endl;
    AffichageGraphique(vertices , tree , nb_vertices , nb_tree_edges , "horizontal_traversal");
    print_vertices_per_depth(depth, nb_vertices);
    cout << endl;
    
    cout << "Performing depth-first traversal of the tree" << endl;
    depth_first_traversal(neighbors , depth , parsing_order , parent , nb_vertices);
    nb_tree_edges = nb_useful_vertices(parent , nb_vertices) - 1;
    tree = new int * [nb_tree_edges];
    for(int i = 0 ; i < nb_tree_edges ; i++) tree[i] = new int [2];
    convert_to_edges(tree , parsing_order , parent , nb_vertices);
    cout << "######################## TRAVERSED TREE ########################" << endl;
    print_tree(tree , nb_tree_edges);
    cout << "################################################################" << endl;
    AffichageGraphique(vertices , tree , nb_vertices , nb_tree_edges , "depth_first_traversal");
    print_vertices_per_depth(depth, nb_vertices);
    //##############################################################################################
    
    //############################ FREE MEMORY #####################################################
    for(int i = 0 ; i < nb_vertices ; i++) delete [] vertices[i];
    for(int i = 0 ; i < nb_tree_edges ; i++) delete [] tree[i];
    delete [] vertices;
    delete [] tree;
    delete [] neighbors;
    delete [] parent;
    delete [] depth;
    delete [] parsing_order;
    //##############################################################################################
    
    return 0;
}


void generate_vertices(int ** vertices , int nb_vertices) {
    vertices[0][0] = 10;
    vertices[0][1] = 10;
    
    for(int i = 1 ; i < nb_vertices ; i++) {
        vertices[i][0] = rand() % 612;
        vertices[i][1] = rand() % 792;
    }
}

void generate_random_graph(int ** vertices , vector<int> * neighbors , int nb_vertices , int * nb_edges , int max_distance) {
    int origin_vertex ,
    end_vertex;
    int real_nb_edges = 0,
    max_counter = 100000;
    vector<int>::iterator it;
    
    for(int i = 0 ; i < *nb_edges ; i++) {
        int counter = 0;
        
        do {
            origin_vertex = rand() % nb_vertices;
            end_vertex = rand() % nb_vertices;
            it = find(neighbors[origin_vertex].begin() , neighbors[origin_vertex].end() , end_vertex);
            counter++;
        } while(counter < max_counter && (end_vertex == origin_vertex || it != neighbors[origin_vertex].end() || distance(vertices, origin_vertex , end_vertex) > max_distance));
        
        if(counter == max_counter) {
            *nb_edges = real_nb_edges;
            return;
        }
        
        if(origin_vertex > end_vertex)
            swap(end_vertex, origin_vertex);
        neighbors[origin_vertex].push_back(end_vertex);
        neighbors[end_vertex].push_back(origin_vertex);
        real_nb_edges++;
    }
}

void horizontal_traversal(vector<int> * neighbors , int * depth , int * parsing_order , int * parent , int nb_vertices) {
    queue<int> vertices_queue;
    bool visited_vertices[nb_vertices];
    int time;
    
    for(int i = 0 ; i < nb_vertices ; i++)
        visited_vertices[i] = false;
    
    visited_vertices[0] = true;
    vertices_queue.push(0);
    time = 2;
    
    while(!(vertices_queue.empty())) {
        int current_vertex = vertices_queue.front();
        vertices_queue.pop();
        
        for(int i = 0 ; i < neighbors[current_vertex].size() ; i++) {
            
            if(!(visited_vertices[neighbors[current_vertex][i]])) {
                depth[neighbors[current_vertex][i]] = depth[current_vertex] + 1;
                parent[neighbors[current_vertex][i]] = current_vertex;
                parsing_order[neighbors[current_vertex][i]] = time;
                vertices_queue.push(neighbors[current_vertex][i]);
                time++;
                visited_vertices[neighbors[current_vertex][i]] = true;
            }
        }
    }
}

void depth_first_traversal(vector<int> * neighbors , int * depth , int * parsing_order , int * parent , int nb_vertices) {
    stack<int> vertices_stack;
    bool visited_vertices[nb_vertices];
    int time = 1;
    
    for(int i = 0 ; i < nb_vertices ; i++)
        visited_vertices[i] = false;
    
    visited_vertices[0] = true;
    parsing_order[0] = time;
    time++;
    vertices_stack.push(0);
    
    while(!(vertices_stack.empty())) {
        int current_vertex = vertices_stack.top();
        
        if(neighbors[current_vertex].empty()) {
            vertices_stack.pop();
        
        } else {
            int current_neighbor = neighbors[current_vertex].front();
            neighbors[current_vertex].erase(neighbors[current_vertex].begin());
                
                if(!(visited_vertices[current_neighbor])) {
                    depth[current_neighbor] = depth[current_vertex] + 1;
                    parent[current_neighbor] = current_vertex;
                    parsing_order[current_neighbor] = time;
                    vertices_stack.push(current_neighbor);
                    time++;
                    visited_vertices[current_neighbor] = true;
            }
        }
    }
}

bool are_linked(vector<int> * neighbors , vector<int> * tested_vertices , int origin_vertex, int end_vertex) {
    
    for(int i = 0 ; i < neighbors[end_vertex].size() ; i++) {
        
        if(neighbors[end_vertex][i] == origin_vertex) {
            return true;
        }
    }
    tested_vertices->push_back(end_vertex);

    for(int i = 0 ; i < neighbors[end_vertex].size() ; i++) {
        vector<int>::iterator it = find(tested_vertices->begin() , tested_vertices->end() , neighbors[end_vertex][i]);
        
        if(it == tested_vertices->end()) {
            if(are_linked(neighbors , tested_vertices , origin_vertex , neighbors[end_vertex][i]))
                return true;
        }
    }
    return false;
}

int nb_useful_vertices(int * depth , int nb_vertices) {
    int n = 0;
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        if(depth[i] != -1) n++;
    }
    return n;
}

int distance(int ** vertices , int origin_vertex , int end_vertex) {
    return pow(vertices[end_vertex][0] - vertices[origin_vertex][0] , 2) + pow(vertices[end_vertex][1] - vertices[origin_vertex][1] , 2);
}