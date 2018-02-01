#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pwd.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc , char * argv[]) {
    struct passwd * pwd = getpwuid(0);
    struct sockaddr_in si_me,
    si_distant;
    socklen_t sock_me_len = sizeof(struct sockaddr_in),
    sock_dist_len = sizeof(struct sockaddr_in);
    int sock_me = socket(PF_INET , SOCK_STREAM , 0),
    send_len = 0,
    recv_len = 0,
    file_size = 0,
    file_fd;
    char recv_buffer[1024],
    send_buffer[1024];
    
    //Create socket
    if(-1 == sock_me) {
        fprintf(stderr , "Error while creating socket\n");
        exit(1);
    }
    //Initialize structs for local address and server address
    si_me.sin_addr.s_addr = htons(INADDR_ANY);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(0);
    si_distant.sin_addr.s_addr = htons(INADDR_ANY);
    si_distant.sin_family = AF_INET;
    si_distant.sin_port = htons(31469);
    //Bind socket to client
    if(-1 == bind(sock_me , (struct sockaddr *)&si_me , sock_me_len)) {
        fprintf(stderr , "Error while binding socket\n");
        exit(2);
    }
    getsockname(sock_me , (struct sockaddr *)&si_me , &sock_me_len);
    printf("Client running on %s:%d\n", inet_ntoa(*(struct in_addr *)&(si_me.sin_addr.s_addr)), ntohs(si_me.sin_port));
    //Connects to server
    if(-1 == connect(sock_me , (struct sockaddr *)&si_distant , sock_dist_len)) {
        fprintf(stderr , "Error while connecting to server\n");
        exit(3);
    }
    //Send pwuid to server
    strcpy(send_buffer , pwd->pw_name);
    if(strlen(send_buffer) != (send_len = write(sock_me , (void *)send_buffer , strlen(send_buffer)))) {
        fprintf(stderr , "Error while sending message\n");
        exit(4);
    }
    //Receive greeting from server
    if(0 >= (recv_len = read(sock_me , (void *)recv_buffer , 1024))) {
        fprintf(stderr , "Error while receiving message\n");
        exit(5);
    }
    printf("%s\n", recv_buffer);
    //Keep prompting the client until he quits
    while(1) {
        char filename[100];
        char path[1024] = "./client_files/";
        printf("Enter the name of the file you want : ");
        fgets(filename , 100 , stdin);
        filename[strlen(filename) - 1] = '\0';
        //Send requested file's name to server
        memset(send_buffer , 0 , sizeof(send_buffer));
        if(-1 == (send_len = write(sock_me , (void *)filename , strlen(filename)))) {
            fprintf(stderr , "Error while sending filename\n");
            exit(4);
        }
        //Receive file size from server
        memset(recv_buffer , 0 , sizeof(recv_buffer));
        if(-1 == (recv_len = read(sock_me , &file_size , sizeof(file_size)))) {
            fprintf(stderr , "Error while receiving file size\n");
            exit(5);
        }
        //Exit if the client requests a file that doesn't exist (file size is 0 byte)
        if(file_size == 0) {
            fprintf(stderr , "The file you requested doesn't exist on the server\n");
            exit(5);
        }
        printf("About to receive %d bytes\n", file_size);
        strcat(path , filename);
        //Open or create the file
        if(-1 == (file_fd = open(path , O_WRONLY | O_CREAT , 0666))) {
            fprintf(stderr , "Couldn't open requested file %s\n" , path);
            exit(4);
        }
        //Receive file from server
        while(file_size > 0) {
            char file_buf[256];
            int recv_bytes = 0,
            written_bytes = 0;
            //Receive up to 256 bytes
            if(0 >= (recv_bytes = read(sock_me , file_buf , 256))) {
                fprintf(stderr , "Error while receiving file\n");
                exit(2);
            }
            //Write received bytes to file
            if(0 >= (written_bytes = write(file_fd , file_buf , recv_bytes))) {
                fprintf(stderr , "Error while writing file\n");
                exit(2);
            }
            //Clean up the buffer and adjust the number of bytes left to receive
            memset(file_buf , 0 , sizeof(file_buf));
            file_size -= recv_bytes;
        }
        close(file_fd);
    }
    return 0;
}