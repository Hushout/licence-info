#include <iostream>
#include "array_functions.h"

/**
 * Prints the array representing a graph
 */
void  print_graph(int ** array , int begin , int end) {
    std::cout << "#### PRINTING GRAPH ####" << std::endl;
    
    for(int i = begin ; i < end ; i++) {
        
        std::cout << "# " << array[i][0] << "\t->\t" << array[i][1] << std::endl;
    }
    std::cout << "#######################################" << std::endl;
}

/**
 * Prints a simple array
 */
void print_array(int * array, int begin , int end) {
    std::cout << "#### PRINTING COMPONENTS ####" << std::endl;
    
    for(int i = begin ; i < end ; i++) {
        
        std::cout << "# " << i << "\t:\t" << array[i] << std::endl;
    }
    std::cout << "########################" << std::endl;

}

/**
 * Prints the array of connected components sizes
 */
void print_comp_array(int ** comp_sizes , int length) {
    
    if(comp_sizes[0][1] == 1) {
        std::cout << "There is\t" << comp_sizes[0][1] << "\tisolated vertex\t" << std::endl;
        
    } else if(comp_sizes[0][1] > 1) {
        std::cout << "There are\t" << comp_sizes[0][1] << "\tisolated vertices\t" << std::endl;
    }
    
    for(int i = 1 ; i < length ; i++) {
        
        if(comp_sizes[i][1] == 1) {
            std::cout << "There is\t" << comp_sizes[i][1] << "\tcomponent with size\t" << comp_sizes[i][0] << std::endl;
            
        } else if(comp_sizes[i][1] > 1) {
            std::cout << "There are\t" << comp_sizes[i][1] << "\tcomponents with size\t" << comp_sizes[i][0] << std::endl;
        }
    }
}


/**
 * Completely sorts the array representing a graph
 * (by order of start AND end of the edges)
 * Use a merge sort
 */
void complete_merge_sort(int ** array , int length) {
    merge_sort(array , 0 , length , 0);
    
    for(int i = 0 ; i < length - 1 ; i++) {
        int unsorted_subset = 0,
        end = i;
        
        for(int j = i + 1 ; j < length ; j++) {
            
            if(array[i][0] == array[j][0]) {
                end++;
                
                if(array[j][1] < array[j - 1][1]) {
                    unsorted_subset = 1;
                }
            }
        }
        end++;
        
        if(unsorted_subset == 1) {
            merge_sort(array , i , end , 1);
        }
    }
}

/**
 * Overloader function of the merge_sort() that creates the necessary
 * work array
 */
void merge_sort(int ** array , int begin , int end , int line) {
    if(end - begin < 2)  {                     // if run size == 1
        return;                                 //   consider it sorted
    }
    // recursively split runs into two halves until run size == 1,
    // then merge them and return back up the call chain
    int middle = (end + begin) / 2;              // iMiddle = mid point
    
    merge_sort(array , begin , middle , line);  // split / merge left  half
    merge_sort(array , middle , end , line);  // split / merge right half
    merge(array , begin , middle , end , line);  // merge the two half runs
}

/**
 * Does the actual sorting
 */
void merge(int ** array , int begin , int middle , int end , int line) {
    int i = begin, j = middle;
    int ** t = new int * [end];
    
    for (int l = begin ; l < end ; l++) {
        t[l] = new int [2];
        t[l][0] = array[l][0];
        t[l][1] = array[l][1];
    }
    
    
    // While there are elements in the left or right runs...
    for (int k = begin ; k < end ; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < middle && (j >= end || array[i][line] <= array[j][line])) {
            t[k][0] = array[i][0];
            t[k][1] = array[i][1];
            i = i + 1;
            
        } else {
            t[k][0] = array[j][0];
            t[k][1] = array[j][1];
            j = j + 1;
        }
    }
    
    for (int l = begin ; l < end ; l++) {
        array[l][0] = t[l][0];
        array[l][1] = t[l][1];
    }
}