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
        printf("%s is a directory\n" , argv[1]);
    else if(S_ISREG(filestat.st_mode&S_IFMT))
        printf("%s is a file\n" , argv[1]);
    else if(S_ISLNK(filestat.st_mode&S_IFMT))
        printf("%s is a link\n" , argv[1]);
    else
        printf("%s is another kind of file\n" , argv[1]);
    return 0;
}