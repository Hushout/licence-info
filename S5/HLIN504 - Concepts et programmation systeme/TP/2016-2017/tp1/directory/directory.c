//
//  directory.c
//  
//
//  Created by Nicolas Stadler on 31/05/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc , char * argv[] , char * arge[]) {
    char * pattern = "PATH" , * separator = ":" , * found = NULL;
    int i = 0;
    
    while(arge[i] && arge[i] != (found = strstr(arge[i] , pattern)))
        i++;
    if(arge[i] == NULL) {
        printf("The pattern %s doesn't exist\n" , pattern);
        return 1;
    } else {
        char * current_working_directory = (char *)malloc(1000);
        current_working_directory = getcwd(current_working_directory , 1000);
        
        char * source = arge[i] + strlen(pattern);
        char * token = strtok(source , separator);
        while(token && strcmp(token , current_working_directory) && strcmp(token , "."))
            token = strtok(NULL , separator);
        if(token)
            printf("This directory %s is executable thanks to : %s\n" , token , current_working_directory);
        else
            printf("This directory %s is NOT executable\n" , current_working_directory);
    }
    return 0;
}