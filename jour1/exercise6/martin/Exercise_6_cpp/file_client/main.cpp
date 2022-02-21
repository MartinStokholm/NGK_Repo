//============================================================================
// Description : file_client in C++, Ansi-style on H2
//============================================================================

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

using namespace std;

// Prottype for reciveFile Funtction
void receiveFile(string fileName, int socketfd);
// for printing error
void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	printf("starting client...\n");
	int sockfd, portno, n;
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		error("ERROR opening socket");
	}
	
	server = gethostname(argv[1]);
	if (server == NULL) {
		error("ERROR no such host";
	}
	printf("Server at: %s, port: %s\n", argv[1], argv[2]);
	printf("Connect..\n");
	bzero((

	
	receiveFile(fileName, sockfd);
}

/**
 * Modtager filstørrelsen og udskriver meddelelsen: "Filen findes ikke" hvis størrelsen = 0
 * ellers
 * Åbnes filen for at skrive de bytes som senere modtages fra serveren (HUSK kun selve filnavn)
 * Modtag og gem filen i blokke af 1000 bytes indtil alle bytes er modtaget.
 * Luk filen, samt input output streams
 *
 * @param fileName Det fulde filnavn incl. evt. stinavn
 * @param sockfd Stream for at skrive til/læse fra serveren
 */

void receiveFile(string fileName, int sockfd)
{
	ifstream file_fr(fileName, std::ios::binary);  // Define input stream
	file_fr.read((char*)Buffer, BUFSIZE);  // Automatic seek!
	file_fr.close();

}

