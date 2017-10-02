//
//  factorial.c
//  
//
//  Created by Nicolas Stadler on 31/05/16.
//
//

#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if(n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main(int argc , char * argv[]) {
    if(argc != 2) {
        printf("You have to run this program with exactly one argument\n");
    } else {
        int number = atoi(argv[1]);
        printf("The factorial of %d is %d\n" , number , factorial(number));
    }
    return 0;
}