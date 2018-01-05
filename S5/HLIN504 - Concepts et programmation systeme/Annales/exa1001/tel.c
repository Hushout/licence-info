#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char *  get_field(char * , int , char);

const int BUF_SIZE = 100;

int main(int argc , char * argv[]) {
    FILE *fp;
    char name[20];
    char buffer[BUF_SIZE];
    memset(buffer , 0 , BUF_SIZE);
    
    if(argc != 3) {
        fprintf(stderr , "You must run this program with exactly 1 argument!\n");
        exit(1);
    }
    if((fp = fopen(argv[1] , "r")) == NULL) {
        fprintf(stderr , "Could not open file %s : %s\n", argv[1], strerror(errno));
        exit(2);
    }
    strcpy(name , argv[2]);
    printf("%s\n", name);
    
    while(fgets(buffer , sizeof(buffer) , fp) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        
        if(!strcmp(name , get_field(buffer , 0 , ':')))
            printf("%s  \t%s\n", get_field(buffer , 2 , ':'), get_field(buffer , 1 , ':'));
    }
    fclose(fp);
    return 0;
}

char * get_field(char * item, int field, char separator) {
    char *token,
    buffer[BUF_SIZE],
    sep_str[2] = {separator , '\0'};
    memset(buffer , 0 , BUF_SIZE);
    
    strcpy(buffer , item);
    token = strtok(buffer , sep_str);
    
    int i = 0;
    while(token && i < field) {
        token = strtok(NULL , sep_str);
        i++;
        //printf("**%s**", token);
    }
    return token;
}