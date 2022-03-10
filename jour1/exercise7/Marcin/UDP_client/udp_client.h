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

#define PORT 9000
#define THIS_IP "10.0.0.2"

using std::cout;

class udp_client{
public:
    udp_client(char* ip, char* cmd);
    ~udp_client();
    int run_client();
private:
    int setup_client(char* ip, char* cmd);

    // IP to destination, supplied at class constructor
    char* otherIP;
    char* cmd_;

    char recvBuf[100];
    char sendBuf[100];
    // Address of this client and the server to communicate with
    sockaddr_in sthis;
    sockaddr_in sother;
    socklen_t sother_len;
    int port_ = PORT;
    int udp_socket;
    
};