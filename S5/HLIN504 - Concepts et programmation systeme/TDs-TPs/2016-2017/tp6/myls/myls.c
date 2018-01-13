#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc , char * argv[]) {
    DIR * directory;
    struct stat filestat;
    struct dirent * dir_entry;
    char path[512];
    
    if(argc != 2) {
        printf("You must run this program with exactly one argument!\n");
        return 1;
    }
    
    if((directory = opendir(argv[1])) == NULL) {
        printf("Can't open directory %s\n" , argv[1]);
        return 2;
    }
    
    while((dir_entry = readdir(directory)) != NULL) {
        printf("%d  " , (u_int)dir_entry->d_ino);
        strcat(strcat(strcpy(path , argv[1]) , "/") , dir_entry->d_name);
        if((lstat(path , &filestat)) == -1) {
            printf("Can't open file %s\n" , path);
            return 3;
        }
        
        if((filestat.st_mode&S_IFMT) == S_IFDIR)
            printf("%s  d  " , dir_entry->d_name);
        else if(S_ISREG(filestat.st_mode&S_IFMT))
            printf("%s  -  " , dir_entry->d_name);
        else if(S_ISLNK(filestat.st_mode&S_IFMT))
            printf("%s  l  " , dir_entry->d_name);
        else
            printf("%s  ?  " , dir_entry->d_name);
        
        if(filestat.st_mode & S_IRUSR) printf("r"); else printf("-");
        if(filestat.st_mode & S_IWUSR) printf("w"); else printf("-");
        if(filestat.st_mode & S_IXUSR) printf("x"); else printf("-");
        if(filestat.st_mode & S_IRGRP) printf("r"); else printf("-");
        if(filestat.st_mode & S_IWGRP) printf("w"); else printf("-");
        if(filestat.st_mode & S_IXGRP) printf("x"); else printf("-");
        if(filestat.st_mode & S_IROTH) printf("r"); else printf("-");
        if(filestat.st_mode & S_IWOTH) printf("w"); else printf("-");
        if(filestat.st_mode & S_IXOTH) printf("x"); else printf("-");
        printf("\n");
    }
    
    return 0;
    
}