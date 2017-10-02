#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int read_word(int, char[]);
void fork_sort(int *);

const int BUF_SIZE = 100;

int main(int argc, char * argv[]) {
    int file_fd , pipe_fd[2];
    char buffer[BUF_SIZE];
    pid_t child_fd;
    
    
    if(argc != 2) {
        fprintf(stderr, "You must run this program with one argument!\n");
        exit (2);
    }
    
    if((file_fd = open(argv[1] , O_RDONLY)) == -1) {
        fprintf(stderr, "Error while opening file : %s\n" , strerror(errno));
        exit (3);
    }
    
    if((pipe(pipe_fd)) == -1) {
        printf("Error while creating pipe\n");
        exit(3);
    }
    
    switch(child_fd = fork()) {
        case -1 :
            fprintf(stderr, "Forking error : %s\n", strerror(errno));
            exit(1);
            break;
        case 0 :
            close(file_fd);
            fork_sort(pipe_fd);
            exit(0);
            break;
        default :
            close(pipe_fd[0]);
            while(read_word(file_fd, buffer)) {
                //printf("%s  ", buffer);
                write(pipe_fd[1] , buffer , sizeof(buffer));
            }
            close(pipe_fd[1]);
            close(file_fd);
            wait(0);
            return 0;
            break;
    }
}




int read_word(int file_fd , char buffer[]) {
    char c;
    int nb_bytes,
    word_started = 0;
    size_t buf_len = 0;
    buffer[0] = '\0';
    
    while(1) {
        if((nb_bytes = read(file_fd , &c , sizeof(char)) <= 0)) {
            if(nb_bytes == -1) {
                fprintf(stderr , "Error while reading from file : %s\n", strerror(errno));
                exit(1);
            } else {
                //printf("Reached End-Of-File\n");
                return 0;
            }
        }
        if(word_started && ((int)c < 97 || (int)c > 122))
            return 1;
        
        if((int)c > 96 && (int)c < 123) {
            word_started = 1;
            buffer[buf_len] = c;
            buffer[++buf_len] = '\0';
        }
    }
    return 0;
}



void fork_sort(int * in_fd) {
    char buffer[BUF_SIZE],
    current_choice[BUF_SIZE];
    int nb_bytes,
    out_fd[2],
    nb_occurences = 1,
    strcomp_return;
    pid_t child_fd;
    
    if(-1 == close(in_fd[1])) {
        printf("Error while closing\n");
        exit(3);
    }
    
    if(read(in_fd[0] , current_choice , sizeof(current_choice)) != 0){
        //printf("%s\n" , buffer);
    } else return;
    
    if(-1 == pipe(out_fd)) {
        printf("Error while creating pipe\n");
        exit(3);
    }
    
    switch(child_fd = fork()) {
        case -1 :
            fprintf(stderr, "Forking error : %s\n", strerror(errno));
            exit(1);
            break;
        case 0 :
            close(in_fd[0]);
            fork_sort(out_fd);
            exit(0);
            break;
        default :
            close(out_fd[0]);
            while(read(in_fd[0] , buffer , sizeof(buffer)) != 0) {
                strcomp_return = strcmp(current_choice , buffer);
                if(strcomp_return == 0)
                    nb_occurences++;
                else if(strcomp_return < 0)
                    write(out_fd[1] , buffer , sizeof(buffer));
                else {
                    write(out_fd[1] , current_choice , sizeof(current_choice));
                    strcpy(current_choice , buffer);
                }
            }
            printf("%s (%d)  ", current_choice , nb_occurences);
            fflush(stdout);
            close(out_fd[1]);
            close(in_fd[0]);
            wait(0);
            break;
    }
    return;
}