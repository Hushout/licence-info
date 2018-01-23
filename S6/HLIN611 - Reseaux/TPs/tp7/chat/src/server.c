#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void init_server(struct sockaddr_in * , socklen_t * , int *);

const char SERV_ADDRESS[20] = "192.168.1.85";
const int PORT_NUMBER = 5555;
const int BACKLOG_SIZE = 5;
const int MSG_LENGTH = 256;
const int USRNAME_LENGTH = 20;
const int SND_LENGTH = USRNAME_LENGTH + MSG_LENGTH + 4;

int main() {
    fd_set master,
    read_fd;
    struct sockaddr_in si_me;
    socklen_t slen_me = sizeof(struct sockaddr_in);
    int sock_fd,
    fd_max = 0,
    set_usrnames[BACKLOG_SIZE];
    char usernames[BACKLOG_SIZE][USRNAME_LENGTH + 1];
    
    /*Initialize server address*/
    init_server(&si_me , &slen_me , &sock_fd);
    
    /*clear the master and temp sets*/
    FD_ZERO(&master);
    FD_ZERO(&read_fd);
    memset(set_usrnames , 0 , BACKLOG_SIZE);
    
    /*Start listening*/
    if(listen(sock_fd , BACKLOG_SIZE) == -1) {
        fprintf(stderr, "Listening error : %s\n", strerror(errno));
        exit(3);
    }

    /*Add the socket listener to the master set*/
    FD_SET(sock_fd , &master);
    fd_max = sock_fd;
    
    /*Main loop*/
    for(;;) {
        read_fd = master;
        if(select(fd_max + 1 , &read_fd , NULL , NULL , NULL) == -1) {
            fprintf(stderr, "Select error : %s\n", strerror(errno));
            exit(3);
        }
        /*Go through all the file descriptors being watched for new data*/
        for(int i = 0 ; i <= fd_max ; i++) {
            if(FD_ISSET(i , &read_fd)) {
                if(i == sock_fd) {
                    /*If we have a new connection*/
                    struct sockaddr_in si_client;
                    int client_fd;
                    char client_ip[20];
                    socklen_t slen_client = sizeof(struct sockaddr_in);
                    memset(&si_client, 0, sizeof(si_client));
                    memset(client_ip, 0, sizeof(client_ip));
                    
                    /*Accept incoming connection*/
                    if((client_fd = accept(sock_fd , (struct sockaddr *)&si_client , &slen_client)) == -1) {
                        fprintf(stderr, "Error while accepting connection : %s\n", strerror(errno));
                    
                    } else {
                        /*Add new client to master set*/
                        getpeername(client_fd, (struct sockaddr *)&si_client, &slen_client);
                        FD_SET(client_fd , &master);
                        fd_max = (client_fd > fd_max ? client_fd : fd_max);
                        printf("New client on %s:%d, socket %d\n", inet_ntoa(si_client.sin_addr), ntohs(si_client.sin_port), client_fd);
                    }
                    
                } else {
                    /*If we receive data from a connected client*/
                    int nb_bytes;
                    char recv_buffer[MSG_LENGTH + 1],
                    send_buffer[MSG_LENGTH + USRNAME_LENGTH + 1];
                    memset(recv_buffer , 0 , MSG_LENGTH + 4);
                    memset(send_buffer , 0 , SND_LENGTH);
                    
                    if((nb_bytes = recv(i, recv_buffer, MSG_LENGTH + 1, 0)) <= 0) {
                        /*If a message isn't received, close the connection with the client*/
                        if(nb_bytes == -1)
                            fprintf(stderr, "Error while receiving message : %s\n", strerror(errno));
                        else if(nb_bytes == 0)
                            fprintf(stderr, "Socket %d hung up\n", i);
                        close(i);
                        set_usrnames[i] = 0;
                        memset(usernames[i] , ' ' , USRNAME_LENGTH + 1);
                        FD_CLR(i , &master);
                        
                    } else {
                        /*Handle the message received from the client*/
                        if(!set_usrnames[i]){
                            /*If the user doesn't have an assigned name yet, set it up*/
                            strcpy(usernames[i] , recv_buffer);
                            strcat(strcpy(send_buffer, usernames[i]), " just joined the chat");
                            set_usrnames[i] = 1;
                            
                        } else {
                            /*Otherwise, treat the new input as a normal message*/
                            strcat(strcat(strcpy(send_buffer, usernames[i]), " : "), recv_buffer);
                        }
                        printf("%s\n", send_buffer);
                        
                        /*Forward the message to all other clients*/
                        for(int j = 0 ; j <= fd_max ; j++) {
                            /*Don't send to the last sender nor to the listener*/
                            if(FD_ISSET(j , &master) && (j != sock_fd) && (j != i) && set_usrnames[j]) {
                                if((nb_bytes = send(j, send_buffer, strlen(send_buffer) + 1, 0)) == -1) {
                                    fprintf(stderr, "Error while sending message to %s : %s\n", usernames[i], strerror(errno));
                                }
                            }
                        }
                    }/*END handling a message*/
                }/*END handling data from a client*/
            }/*END handling a new input*/
        }/*END looping through descriptors*/
    }/*END of the main loop, if you get past that point you performed voodoo magic*/
}

/*Initialize server address*/
void init_server(struct sockaddr_in * si_me, socklen_t * slen_me, int * sock_fd) {
    /*Create socket for the server*/
    if((*sock_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        fprintf(stderr, "Socket error : %s\n", strerror(errno));
        exit(1);
    }
    
    /*Initialize server address. Note that we're letting the system assign a port, so we'll need to
     launch the server before the clients to know which port it is connected to*/
    memset(si_me, 0, *slen_me);
    si_me->sin_addr.s_addr = INADDR_ANY;
    si_me->sin_family = AF_INET;
    si_me->sin_port = htons(PORT_NUMBER);
    
    /*Bind socket to server address*/
    if(bind(*sock_fd, (struct sockaddr *)si_me, *slen_me) == -1) {
        fprintf(stderr, "Binding error : %s\n", strerror(errno));
        exit(2);
    }
    
    /*Get the address of the server, should be 0.0.0.0*/
    char serv_address[20];
    getsockname(*sock_fd, (struct sockaddr *)si_me, slen_me);
    inet_ntop(AF_INET, &(si_me->sin_addr), serv_address, *slen_me);
    printf("The server is listening to %s:%d\n", serv_address, ntohs(si_me->sin_port));
}