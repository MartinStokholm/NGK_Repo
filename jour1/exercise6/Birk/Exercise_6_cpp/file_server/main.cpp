//============================================================================
// Description : file_server in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "iknlib.h"

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void sendFile(string fileName, long fileSize, int outToClient);

/**
 * main starter serveren og venter på en forbindelse fra en klient
 * Læser filnavn som kommer fra klienten.
 * Undersøger om filens findes på serveren.
 * Sender filstørrelsen tilbage til klienten (0 = Filens findes ikke)
 * Hvis filen findes sendes den nu til klienten
 *
 * HUSK at lukke forbindelsen til klienten og filen når denne er sendt til klienten
 *
 * @throws IOException
 *
 */
int main(int argc, char *argv[])
{   
    //variebels for:
    //// sock file descriptor 
    //// new sock file desctriptor
    //// port number that the server accepts data from
    int sockfd, newsockfd, portno;
    // clilen stores the size of the address of the client.
    socklen_t clilen;
    // rx vuffer from bytes read from socket connection
    char buffer[256];
    // sockadd_in hold an internet address.
    //// serv_addr holds the server address.
    //// cli_addr holds the client address.
    struct sockaddr_in serv_addr, cli_addr;
    // n is used to hold the return value from read and write
    int n;
    // This checks that the correct arguments was passed. 
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    // socket() is a system call
    //// The first argument determins if its unix or internet domain
    //// the second argument defines the type of socket.
    ////// Two options, stream and datagram,
    ////// the stream continuesly gets data like reading form a file
    //// the thired argument is the protocal. 
    ////// 0 lets the compiler chose the most appropiate
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Checks if an error occured in opening the socket.
    if (sockfd < 0) 
       error("ERROR opening socket");
    // bzero sets elemets in a buffer to zero. Takes address and legth. 
    bzero((char *) &serv_addr, sizeof(serv_addr));
    // saves the second cmd argument, the portnumber, as a int to portno.
    portno = atoi(argv[1]);
    // setting up the struct server addreess
    //// the first element famility is set to internet
    serv_addr.sin_family = AF_INET;
    //// the address of the host
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    //// port number is converted to network byte order, big ediram
    serv_addr.sin_port = htons(portno);
    // bind bindes a socket to address.
    //// first argument is the socket file
    //// secod argument is the address of type sockaddr
    //// Then the size of of the address
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) 
        {
            error("ERROR on binding");
        }

    // listen() allows the process to lisen for connections 
    //// takes the socket it should lisen on
    //// and the number that can be in cue while one connection.
    listen(sockfd,5);
    //the client address lengt is saved in clilen.
    clilen = sizeof(cli_addr);
    // 
    newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);

    if (newsockfd < 0) 
         error("ERROR on accept");

    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);
    return 0; 
/**
 * Sender filen som har navnet fileName til klienten
 *
 * @param fileName Filnavn som skal sendes til klienten
 * @param fileSize Størrelsen på filen, 0 hvis den ikke findes
 * @param outToClient Stream som der skrives til socket
     */
void sendFile(string fileName, long fileSize, int outToClient)
{
    // TO DO Your own code
}

