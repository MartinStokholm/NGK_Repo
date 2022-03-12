#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <array>
#include "iknlib.h"

using std::cout; using std::endl; using std::vector; using std::string; using std::array;
class TCPServer
{
    public:
        TCPServer(int p);

        int getAccSock();
        int openCSock();
        int startListen();
        char* waitConnection();
        void closeConnection();
        void clearBuffer();


    private:
        const char *extractFileName(const char *fileName);
        struct sockaddr_in address;
        struct sockaddr_in thisAddress;
        int requestSocket = 0;
        int accSocket = 0;
        int port;
        int addrLen;
        char buffer[256];
        string hi = "Hello, traveller!";
        vector<int> connSocket;
};