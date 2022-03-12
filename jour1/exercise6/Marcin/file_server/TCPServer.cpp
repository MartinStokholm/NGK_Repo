#include "TCPServer.h"

TCPServer::TCPServer(int p){
    address.sin_port = htons(p);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    port = p;
    addrLen = sizeof(address);

    thisAddress.sin_port = htons(p);
    thisAddress.sin_family = AF_INET;
    inet_aton("10.0.0.1",(in_addr*) &thisAddress.sin_addr.s_addr);
}


int TCPServer::openCSock(){
    // Create a socket used to accept incoming connections
    requestSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(requestSocket == -1){
        throw "Could not create a server socket \n";
    }
    else{
        return requestSocket;
    }
}

int TCPServer::startListen(){
    // Bind the socket to this IP address and port 9000 
    if(bind(requestSocket, (struct sockaddr *)&thisAddress, sizeof(address)) < 0 ){
        throw "Unable to bind \n";
    }
    // Listen to max 3 connections simultaneously through this socket
    if(listen(requestSocket, 3) < 0){
        throw "Listen error \n";
    }
    return 0;
}


// This function should be in several separate methods instad, but I'm a little too tired to structure things properly
// Awaits incoming request for connection -> Opens a new socket (accSocket)
// Waits for and reads data from acc socket until 0 termination or newline char
// If the file exists, sends file size and file name without path to client
char* TCPServer::waitConnection(){
    clearBuffer();
    accSocket = accept(requestSocket, (struct sockaddr *)&address, (socklen_t*)&addrLen);
    
    int valread;

    read(accSocket, buffer, 100);
    printf("Msg received, \n");
    printf("Msg length = %i \n", strlen(buffer));
    
    char msg[strlen(buffer)+1];
    strcpy(msg, buffer);
    
    cout << "Received message: " << msg << endl;
    
    const char* filename;
    // Extract filename from received msg. If it exists, send it back to Client
    filename = extractFileName(msg);
    cout << filename << "\n";
    char* this_file = (char*)malloc(strlen(filename) + 1);
    strcpy(this_file, filename);
    long f_size = check_File_Exists(msg);
    if (f_size > 0){
        cout << "Filename is : " << this_file << endl;
        write(accSocket, this_file, strlen(filename) + 1);
    }
    return buffer;
}

// Needed in main cause sendFile is not here...
int TCPServer::getAccSock(){
    if(accSocket != 0){
        return accSocket;
    }
    else{
        return -1;
    }
}

void TCPServer::clearBuffer(){
    memset(buffer, 0, sizeof(buffer));
}

// Taken from iknlib.h ... why didn't we just use that library's function again?
const char* TCPServer::extractFileName(const char *fileName)
{
    char *ecn;
    return ((ecn = (char *)strrchr(fileName,'/'))==0 ? fileName : ++ecn);
}

void TCPServer::closeConnection(){
    close(accSocket);
    close(requestSocket);
}