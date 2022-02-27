#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <fcntl.h>

using std::cout;
static int PORT = 9000;
static int BUF_SIZE = 1024;

int downloadFile(int fd, char* filename, int fileSize, char* buffer);

// Available files: /home/lorn.mp3
int main(void){
    // Type in the file name to download with PATH
    printf("Enter file name: \n");
    char input[100];
    fgets(input, 99, stdin);
    char serverMsg[50];
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    const char* msg;
    char buffer[BUF_SIZE] = {0};

    // Create a socket to connect to the server
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Could not create socket\n");
        return -1;
    }
    printf("Socket created\n");

    // Setup the socket data 
    serv_addr.sin_family = AF_INET;     // Ip4
    serv_addr.sin_port = htons(PORT);   // Port 9000
    // Convert address to ip4  
    if(inet_pton(AF_INET, "10.0.0.1", &serv_addr.sin_addr) <= 0){
        printf("Invalid address/Not supported \n");
        return -1;
    }

    printf("Address converted \n");
    // Connect 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("Conection Failed \n");
        return -1;
    }
    // Send file name to the server. +1 for null termination 
    send(sock, input, strlen(input) + 1, 0);
    // Read back the filename without path. Used to name the downloaded file
    
    valread = read(sock, buffer, BUF_SIZE);
    char comp_str[29] = "No such file on the server!";

    int comp = strcoll(comp_str, buffer);
    if(comp == 0){
        printf("%s\n", buffer);
        return 0;
    }

    printf("Filename : %s\n", buffer);
    char name[strlen(buffer)+ 1];
    strcpy(name, buffer);
    
    int fileSize;
    char sizeC[20];
    valread = read(sock, sizeC, (size_t) 20);
    printf("File size = %s bytes\n", sizeC);
    fileSize = atoi(sizeC);
    downloadFile(sock, name, fileSize, buffer);
    return 0;
}
// Parameters: fd : socket file descriptor
// char* filename : name of the file
// int filesize : size of the file in bytes
// char* buffer : buffer to process data through
int downloadFile(int fd, char* filename, int fileSize, char* buffer){
    // How many 1024 byte packets is the client going to receive
    int num_loops = fileSize/BUF_SIZE;
    // Last packet will be less than 1024 byte
    int lastSize = fileSize % BUF_SIZE;

    // Make a new file to save the data in. All user privileges
    int outfile = creat(filename, S_IRUSR | S_IWUSR | S_IXUSR);
    // Send a short message to sync client with server
    const char msgCmf[4] = "c\0";
    int totalBytes = 0;
    for(int i = 0; i < num_loops; i++){
        // Read from the stream
        int readBytes = read(fd, buffer, BUF_SIZE);
        totalBytes += readBytes;
        // Print download status periodically
        if(i%500 == 0){
            printf("\33[2K\r");     // Overwrites the previous text line
            cout << "    Downloading progress : " << totalBytes << " bytes out of " << fileSize << " ";
        }
        cout << "..."; // For some weird reason, needs this to display progress
        cout << "\r ";
        // Save to file
        write(outfile, buffer, readBytes);
        // Send confirmation msg
        send(fd, &msgCmf, 4, 0);
    }
    
    // Last packet
    int readBytes = read(fd, buffer, lastSize);
    readBytes = write(outfile, buffer, readBytes);
    cout << "\n Download complete. \n";
    return 0;
}