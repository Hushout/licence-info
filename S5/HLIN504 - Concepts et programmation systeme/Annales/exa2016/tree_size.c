#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

int recursive_size(char[]);

const int PATH_LGTH = 1024;

int main(int argc , char * argv[]) {
    
    if(argc != 2) {
        fprintf(stderr , "You must run this program with one argument!\n");
        exit(1);
    }
    /*Call the recursive function on the root file or directory. Done!*/
    int size = recursive_size(argv[1]) / 1024;
    printf("%s  %dKB\n", argv[1] , size);
    
    return 0;
}

/**
 *This function takes a file or directory's path as input and does a recursive traversal
 *of its subfolders to calculate the total size
 */
int recursive_size(char root_path[]) {
    DIR * root_dir;
    struct stat file_stat;
    struct dirent * entry;
    char path[PATH_LGTH];
    int total_bytes = 0;
    
    /*Fill in a stat struct containing the info of the root (current) file or directory*/
    if((lstat(root_path , &file_stat) == -1)) {
        fprintf(stderr , "Can't open %s : %s\n", path , strerror(errno));
        exit(2);
    }
    /*Add the current file or directory's size to the total*/
    total_bytes += (int)file_stat.st_size;
    
    /*If the current file is a directory, recursively call the function on all the files it contains
     except . and ..*/
    if(S_ISDIR(file_stat.st_mode)){
        
        if((root_dir = opendir(root_path)) == NULL) {
            fprintf(stderr , "Can't open %s as a directory: %s\n", root_path , strerror(errno));
            exit(2);
        }
        while((entry = readdir(root_dir)) != NULL) {
            memset(path , 0 , PATH_LGTH);
            strcat(strcat(strcpy(path , root_path), "/"), entry->d_name);
            if(strcmp(entry->d_name , ".") && strcmp(entry->d_name , ".."))
                total_bytes += recursive_size(path);
        }
        closedir(root_dir);
    }
    return total_bytes;
}