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
#include <netinet/in.h>
#include "iknlib.h"
#include "TCPServer.h"
#include <sys/poll.h>

using namespace std;

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
    TCPServer serv(12000);
    // TO DO Your own code
    // Open a new request socket
    try{
        serv.openCSock();
    }
    catch(const char* msg){
        cerr << msg << endl;
    }
    cout << "Starting server... " << endl;

    // Try listening (also binds)
    try{
        serv.startListen();
    }
    catch(const char* msg){
        cerr << msg << endl;
    }

    serv.waitConnection();

}

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

