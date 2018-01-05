//
//  pascal.c
//  
//
//  Created by Nicolas Stadler on 31/05/16.
//
//

#include <stdio.h>
#include <stdlib.h>

int ** generate_pascal_triangle(int);
void print_pascal_triangle(int ** , int);

int main(int argc , char * argv[]) {
    int ** triangle;
    int dimension,
    total;
    
    if(argc != 3) {
        printf("You have to run this program with exactly two argument!\n");
        return 1;
    }
    dimension = atoi(argv[1]);
    total = atoi(argv[2]);
    triangle = generate_pascal_triangle(dimension);
    print_pascal_triangle(triangle , dimension);
    printf("There are %d C(%d,%d) combinations\n", triangle[dimension][total] , dimension , total);
    
    for(int i = 0 ; i <= dimension ; i++)
        free(triangle[i]);
    free(triangle);
    return 0;
}

int ** generate_pascal_triangle(int n) {
    int ** triangle = malloc(sizeof(int *) * n + 1);
    for(int i = 0 ; i <= n ; i++) {
        triangle[i] = malloc(sizeof(int) * i + 1);
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        for(int j = 1 ; j < i ; j++)
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
    }
    return triangle;
}

void print_pascal_triangle(int ** triangle, int dimension) {
    for(int i = 0 ; i <= dimension ; i++) {
        for(int j = 0 ; j <= dimension - i ; j++)
            printf("\t");
        for(int j = 0 ; j <= i ; j++)
            printf("%d\t\t", triangle[i][j]);
        printf("\n");
    }
}