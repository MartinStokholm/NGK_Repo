#pragma once
/*UDP CLIENT WITH IP 10.0.0.2 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

using std::cout;
using std::endl;
using std::string;

class UDP_CLIENT {

public:
// Constructor takes in portnumber, ip and the command that should be sent
	UDP_CLIENT(short unsigned int portnumber, string ip, string cmd) 
			: portnumber_(portnumber), ip_(ip), cmd_(cmd) 
	{
		// assign values to struct sockaddr_in
		server_.sin_family = AF_INET;
		server_.sin_port = htons(portnumber_);
		inet_pton(AF_INET, "ip", &server_.sin_addr);
		// create socket with UDP
		socket_ = socket(AF_INET, SOCK_DGRAM, 0);	
		if (socket_ < 0) error("Failed to create socket");

	}
	// simple function for writing a message and then reading the answer
	int RunClient(){
		cout << "Starting UDP client" << endl;
		// put cmd into buffer for sending			
		writeSocket(cmd_);
		sleep(1); 
		readSocket();
		return 1;
	}

private:
// Variabels and structs
	int n_;
	int socket_;
	unsigned int lenght_;
	short unsigned int portnumber_;
	string ip_;
	string cmd_;
	char recvbuf_[100];
	char sendbuf_[100];

	struct sockaddr_in server_;
	socklen_t serverLenght_; 

// Functions
	void error(const char *errorMsg){
		perror(errorMsg);
		exit(0);
	}

	int writeSocket(const char *msg){
		// Copy msg to buffer for sending
		strcpy(sendbuf_, msg);
		int status = sendto(socket_, sendbuf_, sizeof(sendbuf_), 0, (sockaddr*) &server_, &serverLenght_);		
		cout << "Sending: "<< sendbuf_ << " to: " << ip_ << endl;
		return status;	
	}

	int readSocket() {
		int recvfrom(socket_, recvbuf_, sizeof(recvbuf_), 0, (sockaddr*) &server_, &serverLenght_);
		cout << "Recieved: " <<  << " from: " << ip_ << endl;
		return status;
	}
};
