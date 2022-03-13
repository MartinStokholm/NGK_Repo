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
using std::copy;

class UDP_CLIENT {

public:
	UDP_CLIENT(short unsigned int portnumber, string ip, string cmd) 
			: portnumber_(portnumber), ip_(ip), cmd_(cmd) 
	{
		server_.sin_family = AF_INET;
		server_.sin_port = htons(portnumber_);
		inet_pton(AF_INET, "ip", &server_.sin_addr);

		client_.sin_family = AF_INET;
		inet_pton(AF_INET, clientIp_, &client_.sin_addr);
		client_.sin_port = htons(portnumber_);

		char *sendable = new char[send_.size() + 1];
		copy(send_.begin(), send_.end(), sendable);
		sendable[send_.size()] = '\0';

		char *recieveable = new char[recieve_.size() + 1];
		copy(recieve_.begin(), recieve_.end(), recieveable);
		recieveable[recieve_.size()] = '\0';

		socket_ = socket(AF_INET, SOCK_DGRAM, 0);	
		if (socket_ < 0) error("Failed to create socket");

	}
	~UDP_CLIENT()
	{
		// FREE UP MALLOC
		// delete[] send_
		// delete[] recieve_
	}
	int RunClient(){
		cout << "Starting UDP client" << endl;
		int status = 0;
			
		send_ = cmd_;

		status = sendto(socket_, send_, send_.size, 0, (sockaddr*) &server_, &serverLenght_);		
		cout << "Sending: "<< cmd_ << " to: " << ip_ << endl;

		sleep(1);

		recvfrom(socket_, recieve_, recieve_.size, 0, (sockaddr*) &server_, &serverLenght_);
		cout << "Recieved: " << recieve_ << " from: " << ip_ << endl;
		
		return 1;
	}

private:
// Variabels and structs
	int n_;
	int socket_;
	unsigned int lenght_;
	short unsigned int portnumber_;
	string clientIp_ = "10.0.0.2";
	string ip_;
	string cmd_;
	string recieve_ = "";
	string send_ = "";

	char* sender_;
	char* reciever_;

	struct sockaddr_in server_;
	struct sockaddr_in client_;
	socklen_t serverLenght_; 

// Functions
	void error(const char *errorMsg){
		perror(errorMsg);
		exit(0);
	}
};
