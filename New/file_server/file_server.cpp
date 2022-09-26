/* A simple server in the internet domain using TCP
The port number is passed as an argument 
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm 

Modified: Michael Alrøe
Extended to support file server!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "iknlib.h"

#define STRBUFSIZE 256

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

/**
 * @brief Sends a file to a client socket
 * @param clientSocket socket stream to client
 * @param fileName Name of file to be sent to client
 * @param fileSize Size of file
 */
void sendFile(int clientSocket, const char* fileName, long fileSize)
{
	FILE* file = fopen(fileName, "rb");
	if (file == NULL)
	{
		error("ERROR opening file");
	}
	
	// Send file size
	char fileSizeStr[STRBUFSIZE];
	sprintf(fileSizeStr, "%ld", fileSize);
	write(clientSocket, fileSizeStr, STRBUFSIZE);
	
	// Send file
	char buffer[STRBUFSIZE];
	int n;
	while ((n = fread(buffer, 1, STRBUFSIZE, file)) > 0)
	{
		write(clientSocket, buffer, n);
	}
	
	fclose(file);
}


int main(int argc, char *argv[])
{

	printf("Starting server...\n");

	
	int sockfd, newsockfd, portno;

	socklen_t clilen;
	char bufferRx[BUFSIZE_RX];
	char bufferTx[BUFSIZE_TX];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	// Check if port number is provided	
	if (argc < 2) 
		error("ERROR usage: port");

	// Create socket
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

	// Listen for connections
	printf("Listen...\n");
	listen(sockfd,5);
	
	clilen = sizeof(cli_addr);

	for (;;)
	{
		printf("Accept...\n");
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0) error("ERROR on accept");
		else printf("Accepted\n");

		bzero(bufferRx,sizeof(bufferRx));
		n = read(newsockfd,bufferRx,sizeof(bufferRx));

		if (n < 0) error("ERROR reading from socket");
		printf("Message: %s\n",bufferRx);
		
		snprintf(bufferTx, sizeof(bufferTx), "Got message: %s",bufferRx);

		n = write(newsockfd,bufferTx,strlen(bufferTx));
		if (n < 0) error("ERROR writing to socket");
			
		close(newsockfd);
	}
	close(sockfd);
	return 0; 
}