//
//  argenv.c
//  
//
//  Created by Nicolas Stadler on 31/05/16.
//
//
#include <stdio.h>

int main(int argc , char * argv[] , char * arge[]) {
    int nb_environnement_variables = 0;
    printf("Program launched with %d arguments : " , argc);
    for(int i = 0 ; i < argc ; i++)
        printf("%s " , argv[i]);
    printf("\n");
    
    for(char **env = arge ; *env ; ++env) {
        printf("%s\n" , *env);
        nb_environnement_variables++;
    }
    printf("There are %d environnement variables\n" , nb_environnement_variables);

    return 0;
}