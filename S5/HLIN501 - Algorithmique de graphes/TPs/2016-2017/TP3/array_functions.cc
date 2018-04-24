#include <iostream>
#include "array_functions.h"

using namespace std;

/**
 * Prints the array representing a graph
 */
void print_graph(vector<int> * neighbors , int length) {
    
    for(int i = 0 ; i < length ; i++) {
        cout << "# " << i << "\t->\t";
        
        for(int j = 0 ; j < neighbors[i].size() - 0 ; j++) {
            cout << neighbors[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Prints all of the vertices and their coordinates
 */
void print_vertices(int ** vertices, int length) {
    
    for(int i = 0 ; i < length ; i++) {
        cout << "# " << i << "\t:\t(" << vertices[i][0] << "," << vertices[i][1] << ")" << endl;
    }
}

/**
 * Prints all the vertices at each depth of the tree
 */
void print_vertices_per_depth(int * depth , int nb_vertices) {
    int isolated_vertices = 0;
    vector<int> depths;
    depths.push_back(0);
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        
        if(depth[i] >= (int)depths.size()) {
            depths.resize(depth[i] + 1);
        }
        
        if(depth[i] > -1) {
            depths[depth[i]]++;
            //for(int j = 0 ; j < depths.size() ; j++) cout << depths[j]; cout << endl;
        } else {
            isolated_vertices++;
        }
    }
    
    for(int i = 0 ; i < depths.size() ; i++) {
        if(depths[i] == 1)
            cout << "There is 1 vertex ";
        else
            cout << "There are " << depths[i] << " vertices ";
        cout << "with depth " << i << endl;
    }
    
    if(isolated_vertices > 0) {
        if(isolated_vertices == 1)
            cout << "There is one vertex ";
        else
            cout << "There are " << isolated_vertices << " vertices ";
        cout << "unreachable from 0" << endl;
    }
}

/**
 * Prints the edges of the tree
 */
void print_tree(int ** tree , int nb_edges) {
    
    for(int i = 0 ; i < nb_edges ; i++) cout << "# " << tree[i][0] << "\t->\t" << tree[i][1] << endl;
}

/**
 * Makes an array of edges from an array of parent nodes
 */
void convert_to_edges(int ** tree , int * parsing_order , int * parent , int nb_vertices) {
    int current_index = 0;
    
    for(int i = 1 ; i < nb_vertices ; i++) {
        
        if(parsing_order[i] != -1) {
            tree[current_index][0] = parent[i];
            tree[current_index][1] = i;
            current_index++;
        }
    }
}

/**
 * Completely sorts the array representing a graph
 * (by order of start AND end of the edges)
 * Use a merge sort
 */
void complete_merge_sort(int ** array , int length , int width) {
    int k = 0;
    
    do {
        merge_sort(array , 0 , length , width , k);
        if(width == 1) break;
        
        for(int i = 0 ; i < length - 1 ; i++) {
            int unsorted_subset = 0,
            end = i;
            
            for(int j = i + 1 ; j < length ; j++) {
                
                if(array[i][k] == array[j][k]) {
                    end++;
                    
                    if(array[j][k + 1] < array[j - 1][k + 1]) {
                        unsorted_subset = 1;
                    }
                }
            }
            end++;
            
            if(unsorted_subset == 1) {
                merge_sort(array , i , end , width , k + 1);
            }
        }
        k++;
    } while(k < width - 1);
}

/**
 * Core of the merge sort function
 */
void merge_sort(int ** array , int begin , int end , int width , int line) {
    
    if(end - begin < 2)  {                     // if run size == 1
        return;                                 //   consider it sorted
    }
    // recursively split runs into two halves until run size == 1,
    // then merge them and return back up the call chain
    int middle = (end + begin) / 2;              // iMiddle = mid point
    
    merge_sort(array , begin , middle , width , line);  // split / merge left  half
    merge_sort(array , middle , end , width , line);  // split / merge right half
    merge(array , begin , middle , end , width , line);  // merge the two half runs
}

/**
 * Does the actual sorting
 */
void merge(int ** array , int begin , int middle , int end , int width , int line) {
    int i = begin, j = middle;
    int ** t = new int * [end];
    
    for (int l = begin ; l < end ; l++) {
        t[l] = new int [width];
        
        for(int m = 0 ; m < width ; m++) {
            t[l][m] = array[l][m];
        }
    }
    
    
    // While there are elements in the left or right runs...
    for (int k = begin ; k < end ; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < middle && (j >= end || array[i][line] <= array[j][line])) {
            
            for(int m = 0 ; m < width ; m++) {
                t[k][m] = array[i][m];
            }
            i = i + 1;
            
        } else {
            
            for(int m = 0 ; m < width ; m++) {
                t[k][m] = array[j][m];
            }
            j = j + 1;
        }
    }
    
    for (int l = begin ; l < end ; l++) {
        
        for(int m = 0 ; m < width ; m++) {
            array[l][m] = t[l][m];
        }
    }
}