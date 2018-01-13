#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

int recursive_traversal(char * , int);

int main(int argc , char * argv[]) {
    if(argc != 2) {
        printf("You must run this program with exactly one argument!\n");
        return 1;
    }
    printf("%s\n" , argv[1]);
    return recursive_traversal(argv[1] , 1);
}

int recursive_traversal(char * dir_path , int indentation) {
    DIR * directory;
    struct stat filestat;
    struct dirent * dir_entry;
    char * path;
    
    if((directory = opendir(dir_path)) == NULL) {
        printf("Can't open directory %s\n" , dir_path);
        return 2;
    }
    
    path = malloc(sizeof(char) * 1024);
    while((dir_entry = readdir(directory)) != NULL) {
        strcat(strcat(strcpy(path , dir_path) , "/") , dir_entry->d_name);
        if((lstat(path , &filestat)) == -1) {
            printf("Can't open file %s\n" , path);
            return 4;
        }
        if(S_ISDIR(filestat.st_mode) && strcmp(dir_entry->d_name , ".") && strcmp(dir_entry->d_name , "..")) {
            for(int i = 0 ; i < indentation ; i++)
                printf("  ");
            printf("%s\n" , dir_entry->d_name);
            recursive_traversal(path , indentation + 1);
        }
    }
    free(path);
    closedir(directory);
    
    return 0;
}