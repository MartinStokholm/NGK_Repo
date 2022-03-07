#include "udp_serv.h"

udp_serv::udp_serv(){
    int err = setup_serv();

    if(err < 0){
        cout << "Error setting up the server\n";
        exit(EXIT_FAILURE);
    }

    run_serv();
};

int udp_serv::run_serv(){
    

    bool done = false;
    int recvBytes;

    cout << "Starting server\n";
    while(!done){
        recvBytes = recvfrom(udp_socket, &recvBuf, sizeof(recvBuf), 0, (sockaddr*) &sother, &sother_len);
        if(recvBytes < 0){
            perror("error reading recv\n");
            done = true;
        }
        else{
            // Do something
        }
    }
    return 0;
}

int udp_serv::setup_serv(){
    // Assign address family
    // Convert ip to appropriate format

    inet_aton("10.0.0.1", &sthis.sin_addr);
    sthis.sin_family = AF_INET;
    sthis.sin_port = htons(port);

    // Set up the socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket < 0){
        perror("Error assigning socket\n");
        return -1;
    }
    // sockaddr is generic descriptor, sockaddr_in specifically for the internet
    if(bind(udp_socket, (sockaddr*) &sthis, sizeof(sthis)) == -1){
        perror("error binding\n");
        return -1;
    }
    return 0;
}

