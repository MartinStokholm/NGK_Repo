/* A simple client in the internet domain using TCP
The ip adresse and port number on server is passed as arguments 
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm 

Modified: Michael Alrøe
Extended to support file client!
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h> 

#include "iknlib.h"

#define STRBUFSIZE 1000

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

/**
 * @brief Receives a file from a server socket
 * @param serverSocket Socket stream to server
 * @param fileName Name of file. Might include path on server!
 */

void receiveFile(int socketfd, const char* fileName, long fileSize)
{
	FILE* file = fopen(fileName, "wb");
	if (file == NULL)
	{
		error("ERROR opening file");
	}
	
	// Receive file
	char buffer[STRBUFSIZE];
	int n;
	long bytesReceived = 0;
	while (bytesReceived < fileSize)
	{
		n = read(socketfd, buffer, STRBUFSIZE);
		if (n < 0)
		{
			error("ERROR reading from socket");
		}
		bytesReceived += n;
		fwrite(buffer, 1, n, file);
	}
	
	fclose(file);
}

int main(int argc, char *argv[])
{
	printf("Starting client...\n");

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[BUFSIZE];
    
	if (argc < 3)
	    error( "ERROR usage: ""hostname"",  ""port""");

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	    error("ERROR opening socket");

	server = gethostbyname(argv[1]);
	if (server == NULL) 
	    error("ERROR no such host");

	printf("Server at: %s, port: %s\n",argv[1], argv[2]);

	printf("Connect...\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	    error("ERROR connecting");

	printf("Please enter the message: ");
	fgets(buffer,sizeof(buffer),stdin);
	n = write(sockfd,buffer,strlen(buffer));  // socket write
	if (n < 0) 
	    error("ERROR writing to socket");
	
    bzero(buffer,sizeof(buffer));
	//n = read(sockfd,buffer,sizeof(buffer));  // socket read
	n = recv(sockfd, buffer, sizeof(buffer), MSG_WAITALL);
	if (n < 0) 
	    error("ERROR reading from socket");
	printf("\n%s\n",buffer);

    printf("Closing client...\n\n");
	close(sockfd);
	return 0;
}
