#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>

using std::cout; using std::endl; using std::vector; using std::string;
class TCPServer
{
    public:
        TCPServer(int p);

        int openCSock();
        int startListen();
        int waitConnection();



    private:
        const char *extractFileName(const char *fileName);
        struct sockaddr_in address;
        int requestSocket;
        int accSocket;
        int port;
        int addrLen;
        char buffer[256];
        string hi = "Hello, traveller!";
        vector<int> connSocket;
};