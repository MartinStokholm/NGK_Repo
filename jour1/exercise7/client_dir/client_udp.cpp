/* The steps for establish socket on client side
 *
 * Create socket with socket() syscall
 *
 * Connect the socket to address of host server using connect() syscall
 *
 * Send and recieve data. Simple way is to use read() and write() syscalls.
 *
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
#include "iknlib.h"

#define MAXLINE 256

void error(char *msg){
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	char buffer[MAXLINE];

	if (argc < 3) {
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0){ 
		error("ERROR opening socket");
	}
	server = gethostbyname(argv[1]);
	
	if (server == NULL {
		fprintf(stderr, "Failed to find host\n");
		exit(0);		
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr, 
		 ((char *)&serv_addr.sin_addr.s_addr, 
		  server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		error("Failed to connect to server");
	}

	printf("Please enter message to send: ");
	// set buffer to all zero
	bzero(buffer, MAXLINE);
	fgets(buffer, MAXLINE-1, stdin);

	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0){
		error("Failed to write to socket");
	}
	
	bzero(buffer, MAXLINE);
	
	n = read(sockfd, buffer, MAXLINE);
	if (n < 0){
		error("Failed to read from socket");
	}
	printf("%s\n", buffer);
	close(sockfd);
	return 0;
}
