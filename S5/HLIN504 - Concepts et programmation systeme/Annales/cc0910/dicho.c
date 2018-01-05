#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

const int LINE_LGTH = 13;

int split_search(int , char[] , int , int);

int main(int argc , char * argv[]) {
    char *path, *pattern;
    off_t pos;
    int file_fd;
    char buffer[LINE_LGTH + 1]; //un octet de plus pour le '\0'
    buffer[LINE_LGTH] = '\0';
    
    if(argc != 3) {
        fprintf(stderr , "You must run this program with 1 argument!\n");
    }
    path = argv[1];
    pattern = argv[2];
    
    file_fd = open(path , O_RDONLY);
    pos = lseek(file_fd, -13, SEEK_END);
    printf("%d ", (int)pos);
    read(file_fd , (void *)buffer , 13);
    printf("%s", buffer);
    printf("%d\n", split_search(file_fd , pattern , 0 , (int)pos/13));
    close(file_fd);
    return 0;
}

int split_search(int file_fd , char pattern[], int first_line , int last_line) {
    char buffer[9];
    buffer[8] = '\0';
    int comp = 0;
    
    if(last_line - first_line < 1)
        return first_line;
    
    int middle = (last_line + first_line) / 2;
    lseek(file_fd , middle * 13 , SEEK_SET);
    read(file_fd , buffer , 8);
    printf("%d : %s",middle, buffer);
    comp = strcmp(pattern , buffer);
    if(comp < 0) {
        return split_search(file_fd , pattern , first_line , middle);
    } else if(comp > 0) {
        return split_search(file_fd , pattern , middle + 1 , last_line);
    } else {
        return middle;
    }
    return -1;
}