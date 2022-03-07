//============================================================================
// Description : file_server in C++, Ansi-style running in H1
//============================================================================
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// libs for TCP/IP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "iknlib.h"

using namespace std;

// Prototype for sendfile function
void sendFile(const char* fileName, long fileSize, int outToClient);

int main(int argc, char *argv[]){	
	
	// main start serveren og venter på en forbindelse fra en klient
	printf("Starting server...\n");
	int sockfd, newsockfd, portno;

	socklen_t clilen;
	char buffer[BUFSIZE];
	char bufferTx[BUFSIZE];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	// validering af argumenter
	if (argc < 2) 
		error("ERROR no port provided");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	printf("Binding...\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");

	printf("Listen...\n");
	listen(sockfd,5);
	
	clilen = sizeof(cli_addr);

	for (;;)
	{
		printf("Accept...\n");
	
	}
	
	close(sockfd);
	return 0; 
}

/**
 * Sender filen som har navnet fileName til klienten
 *
 * @param fileName Filnavn som skal sendes til klienten
 * @param fileSize Størrelsen på filen, 0 hvis den ikke findes
 * @param outToClient Stream som der skrives til socket
     */
void sendFile(const char*  fileName, long fileSize, int outToClient){
	
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
	if (newsockfd < 0) error("ERROR on accept");
	else printf("Accepted\n");

	bzero(buffer,sizeof(buffer));
	n = read(newsockfd,buffer,sizeof(buffer));
		
	// read from socket
	if (n < 0) error("ERROR reading from socket");

	printf("Message: %s\n",buffer);

	// send confirmation to client
	snprintf(bufferTx, sizeof(bufferTx), "Got message: %s",buffer);

	n = write(newsockfd,bufferTx,strlen(bufferTx));
	if (n < 0) error("ERROR writing to socket");
		
	close(newsockfd);
}
