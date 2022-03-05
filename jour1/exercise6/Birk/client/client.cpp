#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFFER_LENGTH 256

// open socket
// recive information about server from portnumber
// connect to server
// send msg to server 
// read answer from server. 
void error(const char *msg)
{
    perror(msg);
    exit(0);
}


void write_message_to_server(int sockfd, char * buffer, int buf_len)
{
	int n = write(sockfd, buffer, buf_len);
	if (n < 0) 
		error("ERROR writing to socket");  
}

void read_message_from_server(int sockfd, char *msg_from_server, int &msg_len)
{

}


int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    
    char buffer[BUFFER_LENGTH];
    
    // handling user input:
    if (argc < 3)
        fprintf(stderr, "usage %s <hostname> <port>", argv[0]);
    int portno = atoi(argv[2]);
    const char *hostname = argv[1];

    // setup: 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *server;
	// The IP is the name of the server! 
    server = gethostbyname(hostname);
    if (server == NULL)
	{
		error("ERROR: failed to get host by name");
		exit(0);	    
	}    
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	// void bcopy(char *s1, char *s2, int length); 
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR Connecting");


    // user input variebels
    char *answer; 
    int msg_len;
    char msg_from_server[BUFFER_LENGTH];

    do { //
        char buffer[BUFFER_LENGTH];
        printf("enter message to be send to server: %s", hostname);
        fgets(buffer, BUFFER_LENGTH, stdin);

        write_message_to_server(sockfd, buffer, strlen(buffer));
        read_message_from_server(sockfd, msg_from_server, &msg_len);
        
        printf("Do you wish to send another message?");
        fgets(answer,2,stdin);
    } while (answer[0] != 'n');
    



}


