/* Steps for establishing a socket on server side
 * 
 * Create socket with socket() syscall
 * 
 * Bind the socket to an addres using bind() syscall. For a
 * server socket consist of a port number on the host machine
 *
 * Listen for connections with listen() syscall
 *
 * Accept a connection with accept() syscall. This call blocks untill client connects
 *
 * Lastly send and recieve data
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXLINE 256

using namespace std;

void error(char *msg){
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]){

	int sockfd, newsockfd, portno, n;
	char buffer[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	// check that params are passed on run
	if (argc < 2){
		fprintf(stderr, "Error, no port provided, please enter a port number\n");
		exit(1);				
	
	}
	// creating socket for server and assign to sock file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Failed to create socket file descriptor");
		exit(1);
	
	}
	// set all zeroes in server buffer
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	// pass in the port number, from argument for server to listen on
	portno = atoi(argv[1]); // atoi converts from string to int
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	// bind the socket 
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){
		error("Error could not bind socket");
	}
	// listen makes server socket passive so able to listen for clients to connect
	listen(sockfd,5); // second param is the max allowed clients
	
	clilen = sizeof(cli_addr); 
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0){
		error("Error could not accept\n");
	}
	// at this point client should be connected
	bzero(buffer, MAXLINE);

	// read from new socket connection
	n = read(newsockfd, buffer, MAXLINE-1);
	if (n < 0) {
		error("Failed to read from socket");
	}
	printf("Message from client: %s", buffer);

	// write response to client
	n = write(newsockfd, "Server ok", sizeof("Server ok")); 
	if (n < 0) {
		error("Failed to  write to socket");
	}
	return 0;
}





