# TCP-Client/Server

In this exercise we develop a TCP Server that can be used to download a file via a TCP client, which we also develop. The programming language used in this exercise is C++. 

## Server app

To create a TCP server we use linux's socket.h API. In our solution we opted to create a TCP server class, which contains the necessary data and most functions for setting up the server.

socket.h abstracts a fair deal of both TCP and UDP socket functionality into simple functions. A TCP server needs to have a socket which listens to incoming connections. After such a socket has been created, bound and set to listening mode, a client can attempt to connect with a server. 

    // Create a socket used to accept incoming connections
    requestSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Bind the socket to this IP address and port 9000 
    if(bind(requestSocket, (struct sockaddr *)&thisAddress, sizeof(address)) < 0 ){
        throw "Unable to bind \n";
    }
    // Listen to max 3 connections simultaneously through this socket
    if(listen(requestSocket, 3) < 0){
        throw "Listen error \n";
    }

the struct sockaddr_in, cast into sockaddr* , is used to store port number, IP address and the family of the address, such as IP4, IP6 or even a non-internet based family. This server uses port 9000, IP 10.0.0.1 and IP4 family and is set up in the constructor. 

The server then waits for requests to connect (the 3 way TCP handshake) and accepts the first incoming request, creating a new socket via accept() function.

    accSocket = accept(requestSocket, (struct sockaddr *)&address, (socklen_t*)&addrLen);

Then it reads a string from the socket and checks whether the string matches a directory and a filename on the machine, and if so, attempts to send the file.

## Sending the file

To send the file the server opens a file, reads 1024 bytes of data into the buffer, then sends it via socket via send() command. Reading and sending repeated up to filesize/bufferSize times, and the last time the server sends filesize % bufferSize bytes. This ensures that the correct amount of bytes is sent at all times. In our solution we opted to respond to each 1024 data chunk transfered on the client, so the server waits for the client to save the data.

    // Send file loop
    for(int i = 0; i < num_loops; i++){
        sent = read(fd, &sendBuffer, BUF_SIZE);
        actuallySent += send(outToClient, &sendBuffer, BUF_SIZE, 0);
        read(outToClient, &conf, 4);
    }

## Server client

Unlike the server we opted not to create a whole class for a client which is not supposed to run several times. The client side of a TCP connection needs only to create a socket and request a connection via connect() function to be able send and receive messages.

    // Create a socket to connect to the server
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    ...
    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    ...

The string to send to the server is input upon calling the program. Then the client waits to receive either filesize or an error message, and if succesful, prepares to download the file.

## Downloading the file

To properly download a file the client must create a new file with write privileges enabled, read the correct number of bytes from the socket and write the data read into the new file. The number of loops is again filesize/bufferSize, and after the for loop the client must read filesize % bufferSize bytes. 

    for(int i = 0; i < num_loops; i++){
        // Read from the stream
        int readBytes = read(fd, buffer, BUF_SIZE);
        totalBytes += readBytes;
        // Print download status periodically
        if(i%500 == 0){
            printf("\33[2K\r");     // Overwrites the previous text line
            cout << "    Downloading progress : " << totalBytes << " bytes out of " << fileSize << " ";
        }
        cout << "\r ";
        // Save to file
        write(outfile, buffer, readBytes);
        // Send confirmation msg
        send(fd, &msgCmf, 4, 0);
    }

To print the download status the client keeps track of total no of bytes downloaded, and ideally keep printing it on the same line.

The results of this exercise can be watched in the attached TCPtest.wav video.