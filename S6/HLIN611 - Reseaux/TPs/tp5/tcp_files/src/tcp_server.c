#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void session_handler(int);

int main(int argc , char * argv[]) {
    struct sockaddr_in si_me,
    si_distant;
    int sock_me = socket(PF_INET , SOCK_STREAM , 0),
    session_fd;
    pid_t session_pid;
    socklen_t sock_me_len = sizeof(struct sockaddr_in),
    session_fd_len = sizeof(struct sockaddr_in);
    
    //Create socket
    if(-1 == sock_me) {
        fprintf(stderr , "Error while creating socket\n");
        exit(1);
    }
    //Initializes sockaddr with server info
    si_me.sin_addr.s_addr = htons(INADDR_ANY);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(31469);
    //Bind socket to server
    if(-1 == bind(sock_me , (struct sockaddr *)&si_me , sock_me_len)) {
        fprintf(stderr , "Error while binding socket\n");
        exit(2);
    }
    getsockname(sock_me , (struct sockaddr *)&si_me , &sock_me_len);
    printf("Server running on %s:%d\n", inet_ntoa(*(struct in_addr *)&(si_me.sin_addr.s_addr)), ntohs(si_me.sin_port));
    //Starts listening to connections
    if(-1 == listen(sock_me , 5)) {
        fprintf(stderr , "Error while listening\n");
        exit(3);
    }
    
    while(1) {
        //When receiving connection
        if(-1 == (session_fd = accept(sock_me , (struct sockaddr *)&si_distant , &session_fd_len))) {
            fprintf(stderr , "Error while accepting client\n");
            exit(4);
        }
        
        //Fork, to let a subprocess handle a current client while the main process goes back to accepting new connections
        switch(session_pid = fork()) {
            case -1 :
                fprintf(stderr , "Error while creating fork\n");
                exit(5);
                break;
                //Subprocess gets client info and displays it, then handles its request
            case 0 :
                getsockname(session_fd , (struct sockaddr *)&si_distant , &session_fd_len);
                getpeername(session_fd , (struct sockaddr *)&si_distant , &session_fd_len);
                printf("Client running on %s:%d\n", inet_ntoa(*(struct in_addr *)&(si_distant.sin_addr.s_addr)), ntohs(si_distant.sin_port));
                session_handler(session_fd);
                exit(0);
                break;
                //Main process closes connection to the client and goes back to listening
            default :
                close(session_fd);
                break;
        }
    }
}

void session_handler(int session_fd) {
    char recv_buffer[1024],
    send_buffer[1024],
    path[1024];
    int send_len,
    recv_len,
    file_fd,
    file_size;
    struct stat file_st;
    
    //Receive pwuid from the client
    if(0 >= (recv_len = read(session_fd , recv_buffer , 1024))) {
        fprintf(stderr , "Error while receiving message\n");
        exit(1);
    }
    //Send greeting to client
    strcat(strcpy(send_buffer , "Hey there, ") , recv_buffer);
    if(strlen(send_buffer) != (send_len = write(session_fd , send_buffer , strlen(send_buffer)))) {
        fprintf(stderr , "Error while sending message\n");
        exit(2);
    }
    while(1) {
        //Receive requested file's name
        memset(recv_buffer , 0 , sizeof(recv_buffer));
        if(0 >= (recv_len = read(session_fd , recv_buffer , 1024))) {
            fprintf(stderr , "Error while receiving filename\n");
            exit(3);
        }
        //Open file and determine its size
        strcat(strcpy(path , "./server_files/") , recv_buffer);
        printf("Client is requesting file %s\n" , path);
        if(-1 == (file_fd = open(path , O_RDONLY))) {
            fprintf(stderr , "Couldn't open requested file\n");
            exit(4);
        }
        stat(path , &file_st);
        file_size = (int)file_st.st_size;
        //Send file size
        if(sizeof(int) != (send_len = write(session_fd , &file_size , sizeof(int)))) {
            fprintf(stderr , "Error while reading file\n");
            exit(2);
        }
        //Start sending file
        while(file_size > 0) {
            char file_buf[256];
            int sent_bytes = 0,
            read_bytes = 0;
            //Read the file, 256 bytes at a time (less when reaching end of file)
            if(0 >= (read_bytes = read(file_fd , file_buf , 256))) {
                fprintf(stderr , "Error while reading file\n");
                exit(2);
            }
            //Send read bytes to client
            if(-1 == (sent_bytes += write(session_fd , file_buf , read_bytes))) {
                fprintf(stderr , "Error while sending file\n");
                exit(2);
            }
            memset(file_buf , 0 , sizeof(file_buf));
            file_size -= sent_bytes;
        }
        close(file_fd);
        memset(path , 0 , strlen(path));
    }
}