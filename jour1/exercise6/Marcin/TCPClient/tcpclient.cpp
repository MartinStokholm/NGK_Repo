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

// Attempts to download a file from a specified server
// Available files: /home/ase/Storage/lorn.mp3 , /home/ase/Storage/furi_ost.zip 
int main(int argc, char* argv[]){
    // Type in the file name to download with PATH
    if(argc < 3){
        cout << "Incorrect number of arguments.\n";
        cout << "Usage: file_client <serv_ip> <path_to_file>\n";
        return 0;
    }
    // Try assign ip and input to user args
    char *IP = (char*)malloc(sizeof(char)*80);
    char *input = (char*)malloc(sizeof(char)*80);
    try{
        strcpy(IP, argv[1]);
        strcpy(input, argv[2]);
    }
    catch(std::overflow_error err){
        cout << "Buffer overflow: too many characters in argument \n";
        return -1;
    }

    char serverMsg[50];
    int sock = 0, valread;
    const char* msg;
    char buffer[BUF_SIZE] = {0};

    // Create a socket to connect to the server
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Could not create socket\n");
        return -1;
    }

    // Setup the socket data 
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;     // Ip4
    serv_addr.sin_port = htons(PORT);   // Port 9000

    // Convert address to ip4  
    if(inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0){
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
    printf("Requesting : %s, len %ld \n", input, strlen(input));
    input[strlen(input) +1] = '\0'; 
    int bytes = send(sock, input, strlen(input) + 1, 0);
    printf("Amount of bytes sent = %i\n", bytes);
    
    // Read back the filename without path. Used to name the downloaded file
    // If file doesn't exist, print error msg and quit
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
    char sizeC[20];     // Could have used buffer here instead??
    valread = read(sock, buffer, (size_t) 20);
    printf("File size = %s bytes\n", buffer);
    fileSize = atoi(buffer);
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