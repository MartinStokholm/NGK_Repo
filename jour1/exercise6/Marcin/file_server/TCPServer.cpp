#include "TCPServer.h"

TCPServer::TCPServer(int p){
    port = p;
    address.sin_port = htons(p);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    addrLen = sizeof(address);
}

int TCPServer::openCSock(){
    requestSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(requestSocket == -1){
        throw "Could not create a server socket \n";
    }
    else{
        return requestSocket;
    }
}

int TCPServer::startListen(){
    if(bind(requestSocket, (struct sockaddr *)&address, sizeof(address)) < 0 ){
        throw "Unable to bind \n";
    }

    if(listen(requestSocket, 3) < 0){
        throw "Listen error \n";
    }
    return 0;
}


// This function should be in several separate methods instad, but I'm a little too tired to structure things properly
// Awaits incoming request for connection -> Opens a new socket (accSocket)
// Waits for and reads data from acc socket until 0 termination or newline char
// Extracts filename
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

int TCPServer::getAccSock(){
    if(accSocket != 0){
        return accSocket;
    }
    else{
        return -1;
    }
}

void TCPServer::clearBuffer(){
    //memset(buffer, 0, sizeof(buffer));
    buffer[0] = 0;   // Apparently this works just as well
}

const char* TCPServer::extractFileName(const char *fileName)
{
    char *ecn;
    return ((ecn = (char *)strrchr(fileName,'/'))==0 ? fileName : ++ecn);
}

void TCPServer::closeConnection(){
    close(accSocket);
    close(requestSocket);
}