#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

const char CLIENT_ADRRESS[20] = "192.168.1.85";
const int PORT_NUMBER = 0;
const int MSG_LENGTH = 1024;
const int USRNAME_LENGTH = 20;
const int RCV_LENGTH = USRNAME_LENGTH + MSG_LENGTH + 4;

int main(int argc, char * argv[]) {
    fd_set master,
    read_fd;
    struct sockaddr_in si_me,
    si_server;
    socklen_t slen_me = sizeof(struct sockaddr_in),
    slen_server = sizeof(struct sockaddr_in);
    int sock_fd,
    fd_max;
    
    if(argc != 2) {
        fprintf(stderr, "You need to run this program with exactly one argument!\n");
        exit(1);
    }
    
    /*Extract server address and port from the argument passed with format 192.168.1.0:5555*/
    int server_port;
    char serv_address[20];
    char * token;
    token = strtok(argv[1], ":");
    strcpy(serv_address, token);
    token = strtok(NULL, ":");
    server_port = atoi(token);
    
    /*Create socket for the client*/
    if((sock_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        fprintf(stderr, "Socket error : %s\n", strerror(errno));
        exit(2);
    }
    
    /*clear the master set*/
    FD_ZERO(&master);
    FD_ZERO(&read_fd);
    
    /*Initialize client address*/
    memset(&si_me, 0, slen_me);
    si_me.sin_addr.s_addr = INADDR_ANY;
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT_NUMBER);
    
    /*Initialize server address*/
    memset(&si_server, 0, slen_me);
    si_server.sin_addr.s_addr = inet_addr(serv_address);
    si_server.sin_family = AF_INET;
    si_server.sin_port = htons(server_port);
    
    /*Bind socket to client address*/
    if(bind(sock_fd, (struct sockaddr *)&si_me, slen_me) == -1) {
        fprintf(stderr, "Binding error : %s\n", strerror(errno));
        exit(3);
    }
    
    /*Get the address of the client, should be 0.0.0.0*/
    char client_address[20];
    getsockname(sock_fd, (struct sockaddr *)&si_me, &slen_me);
    inet_ntop(AF_INET, &(si_me.sin_addr), client_address, slen_me);
    printf("The client is running on %s:%d\n", client_address, ntohs(si_me.sin_port));
    
    /*Add the socket listener and stdin to the master set*/
    FD_SET(sock_fd , &master);
    FD_SET(STDIN_FILENO , &master);
    fd_max = (sock_fd > STDIN_FILENO ? sock_fd : STDIN_FILENO);
    
    /*Connect to server*/
    if(connect(sock_fd, (struct sockaddr *)&si_server, slen_server) == -1) {
        fprintf(stderr, "Connection error : %s\n", strerror(errno));
        exit(4);
    }
    getpeername(sock_fd, (struct sockaddr *)&si_server, &slen_server);
    printf("Reached server at %s:%d\n", inet_ntoa(si_server.sin_addr), ntohs(si_server.sin_port));
    /*Prompt the user for their name before getting in the main loop*/
    char username[USRNAME_LENGTH + 1];
    int nb_char;
    printf("Choose a nickname for this session : ");
    fflush(stdout);
    nb_char = read(0 , username , USRNAME_LENGTH + 1);
    username[nb_char - 1] = '\0';
    if((send(sock_fd, username, strlen(username) + 1, 0)) == -1) {
        fprintf(stderr, "Error while sending username to server : %s\n", strerror(errno));
        exit(5);
    }
    printf("_____________________________________________________\n");
    /*Main loop*/
    for(;;) {
        read_fd = master;
        if(select(fd_max + 1 , &read_fd , NULL , NULL , NULL) == -1) {
            fprintf(stderr, "Select error : %s\n", strerror(errno));
            exit(3);
        }
        for(int i = 0 ; i <= fd_max ; i++) {
            if(FD_ISSET(i , &read_fd)) {
                int nb_bytes;
                char recv_buffer[RCV_LENGTH],
                send_buffer[MSG_LENGTH + 1];
                memset(recv_buffer , 0 , RCV_LENGTH);
                memset(send_buffer , 0 , MSG_LENGTH + 1);
                
                if(i == STDIN_FILENO) {
                    /*If user input*/
                    nb_bytes = read(0, send_buffer, MSG_LENGTH + 1);
                    send_buffer[nb_bytes - 1] = '\0';
                    if((nb_bytes = send(sock_fd, send_buffer, strlen(send_buffer) + 1, 0)) == -1) {
                        fprintf(stderr, "Error while sending message to server : %s\n", strerror(errno));
                    }

                } else {
                    /*If data from the server*/
                    if((nb_bytes = recv(i, recv_buffer, RCV_LENGTH, 0)) <= 0) {
                        if(nb_bytes == -1)
                            fprintf(stderr, "Error while receiving message : %s\n", strerror(errno));
                        else if(nb_bytes == 0)
                            fprintf(stderr, "Socket %d hung up\n", i);
                        close(i);
                        exit(5);
                    } else {
                        recv_buffer[nb_bytes - 1] = '\0';
                        printf("%s\n", recv_buffer);
                    }
                }
            }
        }
    }
    return 0;
}