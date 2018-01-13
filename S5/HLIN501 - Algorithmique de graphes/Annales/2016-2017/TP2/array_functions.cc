#include <iostream>
#include "array_functions.h"

using namespace std;

/**
 * Prints the array representing a graph
 */
void  print_graph(int ** tree , int length) {
    
    for(int i = 0 ; i < length ; i++) {
        cout << "# " << tree[i][0] << "\t->\t" << tree[i][1] << endl;
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
 * Prints all the pairs of vertices and their distance to each other
 */
void print_distances(int ** edges , int length) {
    
    for(int i = 0 ; i < length ; i++) {
        cout << "# " << edges[i][0] << "\t->\t" << edges[i][1] << "\t:\t" << edges[i][2] << endl;
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