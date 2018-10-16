#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc , char * argv[]) {
    if(argc < 2) {
        fprintf(stderr , "You need to run this program with at least one argument!\n");
        exit(1);
    }
    int err = unlink(argv[1]);
    if(err < 0) {
        fprintf(stderr , "Erreur removing ‰%s\n" , argv[1]);
        fprintf(stderr , "Error number : %d. %s\n" , errno , strerror(errno));
    } else
        printf("Removed %s!\n" , argv[1]);
    
    return 0;
}