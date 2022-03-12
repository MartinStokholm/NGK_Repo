#include <stdio.h>
#include <arpa/inet.h>
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
int set_up_client_socket()
{

    // setup: 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd != -1)
	{
		printf("socket for client created");
		return sockfd;
	}
	
	printf("ERROR on creating socket\n");		
	exit(0);
}


struct sockaddr_in define_server_socket(const char * hostname,int portno )
{
	struct sockaddr_in server_address; 
//	struct hostent *server;
//
//	The IP is the name of the server! 
//	server = gethostbyname(hostname);
//	if (server == NULL)
//	{
//		error("ERROR: failed to get host by name");
//		exit(0);	    
//	}    

	bzero((char*) &server_address, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(portno);
	if(inet_pton(AF_INET, hostname, &server_address.sin_addr) <= 0)
	{
		printf("invalid address / not supported\n");
	}
	printf("Server address defined\n");
	return server_address;
}
void connect_client_to_server(	int sockfd, 
								struct sockaddr * server_address, 
								int size_of_server_address)
{

	if (connect(sockfd, server_address, size_of_server_address) < 0)
	{
		error("ERROR Connecting");
	}

	printf("connected to server!\n");
	return;
}        
void close_connection_to_server(int sockfd)
{
	close(sockfd);

}
void write_message_to_server(int sockfd, char * buffer, int buf_len)
{
	int n = write(sockfd, buffer, buf_len);
	if (n < 0 || n != buf_len) 
		error("ERROR writing to socket");  
}

int read_message_from_server(int sockfd, char *msg_from_server, int msg_max_len)
{
	int bytes_read = read(sockfd, msg_from_server, msg_max_len);
	if (bytes_read < 0) 
	{
		printf("error reading\n");
		exit(0);
	}
	return bytes_read; 
}


int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    
    // handling user input:
    if (argc < 3)
        fprintf(stderr, "usage %s <hostname> <port>", argv[0]);
    int portno = atoi(argv[2]);
    const char *hostname = argv[1];

	int sockfd = set_up_client_socket();
	serv_addr = define_server_socket(hostname, portno);
	connect_client_to_server(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // user input variebels
    char *answer; 
    int msg_max_len = 255;
    char msg_from_server[BUFFER_LENGTH];

	char buffer[BUFFER_LENGTH];

	printf("enter message to be send to server: %s\n> ", hostname);
	fgets(buffer, BUFFER_LENGTH, stdin);

	write_message_to_server(sockfd, buffer, strlen(buffer));
	read_message_from_server(sockfd, msg_from_server, msg_max_len);
	printf(msg_from_server);  

    close_connection_to_server(sockfd);        



}


