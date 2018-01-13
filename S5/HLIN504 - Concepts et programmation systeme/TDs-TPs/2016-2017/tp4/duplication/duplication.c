#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int global = 1;

int main(int argc , char * argv[]) {
    int local = 2 , input;
    int * dynamic = malloc(sizeof(int));
    *dynamic = 3;

    if(argc != 2) {
        printf("You must run this program with exactly 1 argument!\n");
        return 1;
    }
    if((input = open(argv[1] , O_RDONLY)) == -1) {
        printf("Can't open %s\n" , argv[1]);
        return 2;
    }
    printf("Pre-fork : I am %d\n" , getpid());
    printf("Pre-fork : global = %d; address = %p\n" , global , &global);
    printf("Pre-fork : local = %d; address = %p\n" , local , &local);
    printf("Pre-fork : *dynamic = %d; dynamic = %p; &dynamic = %p\n" , *dynamic , dynamic , &dynamic);
    printf("Pre-fork : input = %d\n", input);
    
    char s[6];
    strcpy(s , "xxxxx");
    int i = read(input , s , 5);
    if(i != 5) {
        printf("Can't read %s\n" , argv[1]);
        return 3;
    }
    printf("Pre-fork : Reading 5 bytes %s\n", s);
    
    pid_t pid = fork();
    switch(pid) {
        case -1 :
            printf("There was an error while forking\n");
            return 4;
            break;
            
        case 0 :
            printf("Child : I am %d, spawned by %d\n" , getpid() , getppid());
            printf("Child : global = %d; address = %p\n" , global , &global);
            printf("Child : local = %d; address = %p\n" , local , &local);
            printf("Child : *dynamic = %d; dynamic = %p; &dynamic = %p\n" , *dynamic , dynamic , &dynamic);
            printf("Child : input = %d\n", input);
            char s[3];
            strcpy(s , "xx");
            int i = read(input , s , 2);
            if(i != 2) {
                printf("Can't read %s\n" , argv[1]);
                return 5;
            }
            printf("Child : Reading 2 bytes %s\n", s);
            
            global += 10; local += 10; *dynamic += 10;
            printf("Child then : I am %d, spawned by %d\n" , getpid() , getppid());
            printf("Child then : global = %d; address = %p\n" , global , &global);
            printf("Child then : local = %d; address = %p\n" , local , &local);
            printf("Child then : *dynamic = %d; dynamic = %p; &dynamic = %p\n" , *dynamic , dynamic , &dynamic);
            printf("Child then : input = %d\n", input);
            sleep(6);
            break;
            
        default :
            global += 100; local += 100; *dynamic += 100;
            printf("Parent then : I am %d, spawned by %d\n" , getpid() , getppid());
            printf("Parent then : global = %d; address = %p\n" , global , &global);
            printf("Parent then : local = %d; address = %p\n" , local , &local);
            printf("Parent then : *dynamic = %d; dynamic = %p; &dynamic = %p\n" , *dynamic , dynamic , &dynamic);
            printf("Parent then : input = %d\n", input);
            close(input);
            break;
    }
    
    return 0;
}