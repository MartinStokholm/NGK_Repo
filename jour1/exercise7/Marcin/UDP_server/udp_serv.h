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

class udp_serv{
public:
    udp_serv();
    int run_serv();
    
private:
    int setup_serv();
    int cpyUptime();
    int cpyLoadAvg();
    bool checkCmd();
    void clearBufs();
    
    char recvBuf[100];
    char sendBuf[100];
    sockaddr_in sthis;
    sockaddr_in sother;
    socklen_t sother_len;
    int port = 9000;
    int udp_socket;
    const char* accCmd[4] = {"U", "u", "L", "l"};
    
};
