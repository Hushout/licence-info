#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "array_functions.h"

void graph_random(int ** , int , int);
void connected_components(int ** , int * , int , int);
void components_sizes(int* , int , int , int **);
void connected_components_opti(int ** , int * , int , int);

int main(int argc , char * argv[]){
    srand(time(NULL));
    clock_t t;
    int nb_vertices;     // Nombre de sommets.
    int nb_edges;     // Nombre d'aretes.

    if(argc == 1) {
        std::cout << "Enter the number of vertices : ";
        std::cin >> nb_vertices;
        std::cout << "Enter the number of edges : ";
        std::cin >> nb_edges;

    } else {
        char *p;
        nb_vertices = (int)strtol(argv[1] , &p , 10);
        nb_edges = (int)strtol(argv[2] , &p , 10);
    }

    int ** edges = new int * [nb_edges];    // Tableau des aretes.
    int * comp = new int [nb_vertices];       // comp[i] est le numero de la composante contenant i.
    int ** comp_sizes = new int * [nb_vertices];

    for(int i = 0 ; i < nb_edges ; i++) {
        edges[i] = new int [2];
    }

    for(int i = 0 ; i < nb_vertices ; i++) {
        comp_sizes[i] = new int [2];
        comp_sizes[i][0] = i + 1;
        comp_sizes[i][1] = 0;
    }

    graph_random(edges , nb_edges , nb_vertices);
    complete_merge_sort(edges , nb_edges);
    print_graph(edges, 0 , nb_edges);

    std::cout << std::endl << "Using standard algorithm for finding connected components" << std::endl;
    t = clock();
    connected_components(edges , comp, nb_edges, nb_vertices);
    t = clock() - t;
    std::cout << "#########################################################" << std::endl;
    components_sizes(comp , nb_edges , nb_vertices , comp_sizes);
    merge_sort(comp_sizes, 0, nb_vertices, 0);
    print_comp_array(comp_sizes , nb_vertices);
    std::cout << "Connected components calculated in " << (float)t/CLOCKS_PER_SEC << "s with the standard algorithm" << std::endl << std::endl;

    std::cout << "Using optimised algorithm for finding connected components" << std::endl;
    t = clock();
    connected_components_opti(edges, comp , nb_edges , nb_vertices);
    t = clock() - t;
    std::cout << "##########################################################" << std::endl;
    components_sizes(comp , nb_edges , nb_vertices , comp_sizes);
    merge_sort(comp_sizes, 0, nb_vertices, 0);
    print_comp_array(comp_sizes , nb_vertices);
    std::cout << "Connected components calculated in " << (float)t/CLOCKS_PER_SEC << "s with the optimised algorithm" << std::endl << std::endl;

    return 0;
}

void graph_random(int ** edges , int nb_edges , int nb_vertices) {

    for(int i = 0 ; i < nb_edges ; i++) {
        edges[i][0] = rand() % nb_vertices;
        edges[i][1] = rand() % nb_vertices;
    }
}

void connected_components(int ** edges , int * comp , int nb_edges , int nb_vertices) {

    for(int i = 0 ; i < nb_vertices ; i++) {
        comp[i] = i;
    }

    for(int i = 0 ; i < nb_edges ; i++) {

        if(comp[edges[i][0]] != comp[edges[i][1]]) {
            int aux = comp[edges[i][0]];

            for(int k = 0 ; k < nb_vertices ; k++) {

                if(comp[k] == aux) {
                    comp[k] = comp[edges[i][1]];
                }
            }
        }
    }
}

void connected_components_opti(int ** edges , int * comp , int nb_edges , int nb_vertices) {
    /*std::vector< std::vector<int> >  components (nb_vertices , std::vector<int> (0));

    for(int i = 0 ; i < nb_vertices ; i++) {
        components[i].push_back(i);
        comp[i] = i;


    }

    for(int i = 0 ; i < nb_edges ; i++) {

        if(comp[edges[i][0]] != comp[edges[i][1]]) {
            int comp_begin = comp[edges[i][0]],
            comp_end = comp[edges[i][1]];

            if(components[comp_begin].size() <= components[comp_end].size()) {
                int size = (int)components[comp_begin].size();

                for(int j = 0 ; j < size ; j++) {
                    int t = components[comp_begin].back();
                    components[comp_begin].pop_back();
                    components[comp_end].push_back(t);
                    comp[t] = components[comp_end][0];
                }

            } else {
                int size = (int)components[comp_end].size();

                for(int j = 0 ; j < size ; j++) {
                    int t = components[comp_end].back();
                    components[comp_end].pop_back();
                    components[comp_begin].push_back(t);
                    comp[t] = components[comp_begin][0];
                }
            }
        }
    }*/
    std::vector< std::vector<int> >  components (nb_vertices , std::vector<int> (0));

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

           for(int j = 0 ; j < size ; j++) {
               int t = components[comp_begin].back();
               components[comp_begin].pop_back();
               components[comp_end].push_back(t);
               comp[t] = components[comp_end][0];
           }
       }
   }

}

void components_sizes(int * comp , int nb_edges , int nb_vertices , int ** comp_sizes) {
    int * temp_sizes = new int [nb_vertices];

    for(int i = 0 ; i < nb_vertices ; i++) {
        temp_sizes[i] = 0;
        comp_sizes[i][1] = 0;
    }

    for(int i = 0 ; i < nb_vertices ; i++) {
        temp_sizes[comp[i]]++;
    }

    for(int i = 0 ; i < nb_vertices ; i++) {
        comp_sizes[i][0] = i + 1;

        if(temp_sizes[i] > 0) {
            comp_sizes[temp_sizes[i] - 1][1]++;
        }
    }
}
