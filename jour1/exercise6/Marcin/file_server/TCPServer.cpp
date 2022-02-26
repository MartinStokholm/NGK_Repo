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
    accSocket = accept(requestSocket, (struct sockaddr *)&address, (socklen_t*)&addrLen);
    char b;
    int valread = read(accSocket, &b, 1);

    int i = 0, len = 0;
    printf("Msg received, %c\n", b);
    // Check for either null terminator or newline char
    while(b != '\0' && b != '\n' && b != 1){

        buffer[i] = b;
        len++;
        i++;
        valread = read(accSocket, &b, 1);
    }
    printf("Loop 1 : \n");
    printf("Msg length = %i \n", len);
    
    char msg[len + 1];
    strcpy(msg, buffer);
    msg[len + 1] = '\0';
    
    cout << "Received message: " << msg << endl;
    cout << "Loop end\n" << endl;
    
    const char* filename;
    
    // Get filename from received msg
    filename = extractFileName(msg);
    char* this_file = (char*)malloc(strlen(filename) + 1);
    strcpy(this_file, filename);
    cout << "Filename is : " << this_file << endl;
    write(accSocket, this_file, strlen(filename) + 1);


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

const char* TCPServer::extractFileName(const char *fileName)
{
    char *ecn;
    return ((ecn = (char *)strrchr(fileName,'/'))==0 ? fileName : ++ecn);
}

void TCPServer::closeConnection(){
    close(accSocket);
    close(requestSocket);
}