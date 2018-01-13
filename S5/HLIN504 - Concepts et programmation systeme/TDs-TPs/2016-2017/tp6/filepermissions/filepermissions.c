#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc , char * argv[]) {
    struct stat filestat;
    
    if(argc != 2) {
        printf("You must run this program with exactly one argument!\n");
        return 1;
    }
    if((lstat(argv[1] , &filestat)) == -1) {
        printf("Can't open file %s\n" , argv[1]);
        return 2;
    }
    
    if((filestat.st_mode&S_IFMT) == S_IFDIR)
        printf("%s d " , argv[1]);
    else if(S_ISREG(filestat.st_mode&S_IFMT))
        printf("%s - " , argv[1]);
    else if(S_ISLNK(filestat.st_mode&S_IFMT))
        printf("%s l " , argv[1]);
    else
        printf("%s ? " , argv[1]);
    
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

    return 0;
}