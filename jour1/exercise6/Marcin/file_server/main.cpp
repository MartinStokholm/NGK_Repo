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
#include <fcntl.h>

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
    TCPServer serv(9000);
    // TO DO Your own code
    // Open a new request socket
    try{
        serv.openCSock();
    }
    catch(const char* msg){
        cerr << msg << endl;
    }
    cout << "Starting server... " << endl;

    bool done = false;
    // Try listening (also binds)
    try{
        serv.startListen();
    }
    catch(const char* msg){
        cerr << msg << endl;
        return 1;
    }

    char* filename = (char*)malloc(sizeof(char)*100);
    //  If file exists and size > 0, send the file via TCP accSocket
    char rejectBuf[50] = "No such file on the server!\0";

    while(!false){
        cout << "Ready to receive connection. \n";
        strcpy(filename, serv.waitConnection());
        cout << "Checking file name...\n";
        long f_size = check_File_Exists(filename);
        if (f_size > 0){
            cout << "Found the file " << f_size << "\n";
            char f_size_str[20];
            strcpy(f_size_str, to_string(f_size).c_str());
            cout << f_size_str << " sent \n";
            writeTextTCP(serv.getAccSock(), f_size_str);
            usleep(1000);
            sendFile(filename, f_size, serv.getAccSock());
        }
        else{
            writeTextTCP(serv.getAccSock(),rejectBuf);
            cout << "Couldn't find the file. Closing connection\n";
            close(serv.getAccSock());
        }
        usleep(500);
    }
    serv.closeConnection();
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
    // Check open close
    int fd = open(fileName.c_str(), O_RDONLY);
    if(fd < 1){
        cout << "Failed to open the file...\n";
        return;
    }
    cout <<"Succesfully opened the file\n";
    size_t BUF_SIZE = 1024;
    // 1000 bytes buffer
    char sendBuffer[BUF_SIZE];
    ssize_t sent; 
    long actuallySent = 0;
    int num_loops = fileSize/BUF_SIZE;
    char conf[4];
    cout << "Starting file transfer, no of loops: " << num_loops << "\n";
    for(int i = 0; i < num_loops; i++){
        sent = read(fd, &sendBuffer, BUF_SIZE);
        actuallySent += send(outToClient, &sendBuffer, BUF_SIZE, 0);
        read(outToClient, &conf, 4);
    }
    cout << "Actually sent: " << actuallySent << "\n";
    sent = read(fd, &sendBuffer, fileSize % BUF_SIZE);
    cout << "Succesfully read " << sent << " bytes\n";
    send(outToClient, &sendBuffer, sent, 0);
    cout << "File sent\n";

    close(fd);
}

