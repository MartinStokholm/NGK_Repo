#include "udp_client.h"

udp_client::udp_client(char* IP, char* cmd){
    int err = setup_client(IP, cmd);

    if(err < 0){
        cout << "Error setting up the client\n";
        exit(EXIT_FAILURE);
    }
};

udp_client::~udp_client(){
    delete[] otherIP;
    delete[] cmd_;
}

int udp_client::run_client(){
    
    sendBuf[0] = 0;
    recvBuf[0] = 0;
    int recvBytes;

    cout << "Starting client. \n";
    strcpy(sendBuf, cmd_);
    if(strlen(sendBuf) > 1){
        cout << "Invalid command length!\n";
        return -1;
    }
    sother_len = sizeof(sother);
    sendto(udp_socket, sendBuf, 2, 0, (sockaddr*) &sother,sother_len);
    // Wait 1 ms for response
    usleep(1000);
    recvfrom(udp_socket, recvBuf, sizeof(recvBuf), 0, (sockaddr*) &sother, &sother_len);
    std::cout << "Received: \n" << recvBuf << "\n";
    return 0;
}

int udp_client::setup_client(char* IP, char* cmd){
    
    // Allocate memory and copy the supplied arguments
    otherIP = (char*) malloc(sizeof(IP));
    strcpy(otherIP, IP);
    cmd_ = (char*) malloc(sizeof(cmd));
    strcpy(cmd_, cmd);
    
    // Assign address families
    // Convert ip to appropriate format and set addr

    inet_aton(THIS_IP, &sthis.sin_addr);
    sthis.sin_family = AF_INET;
    sthis.sin_port = htons(port_);

    inet_aton(otherIP, &sother.sin_addr);
    sother.sin_family = AF_INET;
    sother.sin_port = htons(port_);
    // Set up the socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket < 0){
        perror("Error assigning socket\n");
        return -1;
    }

    // WE DON'T NEED TO BIND IF WE SENDTO FIRST!!!
    // sendto() automatically binds the socket :)
    return 0;
}

