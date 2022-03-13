#pragma once

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

class UDP_SERVER{

public:
	UDP_SERVER(short unsigned int portnumber) : portnumber_(portnumber) 
	{
		socket_ = socket(AF_INET, SOCK_DGRAM, 0);	
		if (socket_ < 0) error("Failed to create socket");

		lenght_ = sizeof(server_);
		server_.sin_family = AF_INET;
		server_.sin_addr.s_addr = INADDR_ANY;
		server_.sin_port = htons(portnumber_);

		if (bind(socket_,(struct sockaddr *)&server_, lenght_) < 0){
			error("Failed to bind");
		}
		fromlen_ = sizeof(struct sockaddr_in);
		
	}
	int RunServer(){
		cout << "Starting UDP server" << endl;
		n_ = recvfrom(socket_, buf_, 1024, 0, (struct sockaddr *)&from_, &fromlen_);	
		if (n_ < 0) error("Failed to recvfrom");
		write(1, "Recieved a datagram: ", 21);
		write(1, buf_, n_);

		n_ = sendto(socket_, "Got your message\n", 17, 0, (struct sockaddr *)&from_, fromlen_);
		if (n_ < 0) error("Failed to sendto");
		return 1;
	}

private:
	int socket_;
	short unsigned int portnumber_;
	int n_;
	unsigned int lenght_;
	struct sockaddr_in server_;
	struct sockaddr_in from_;
	socklen_t fromlen_;
	char buf_[1024];

	void error(const char *errorMsg){
		perror(errorMsg);
		exit(0);
	}
};
