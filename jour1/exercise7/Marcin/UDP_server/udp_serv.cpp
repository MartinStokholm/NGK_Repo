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
            if(checkCmd()){
                std::cout << "Sent data\n";
                clearBufs();
            }
            else{
                std::cout << "Unrecognized command.\n";
            }
        }
    }
    return 0;
}

bool udp_serv::checkCmd(){
    std::cout << "cmd : " << recvBuf << "\n";
    for(int i = 0; i < 4; i++){
        if(strcoll(accCmd[i], recvBuf) == 0){
            if(accCmd[i] == "U" || accCmd[i] == "u"){
                cpyUptime();
                sendto(udp_socket, &sendBuf, sizeof(sendBuf), 0, (sockaddr*) &sother, sother_len);
                return true;
            }
            else if(accCmd[i] == "L" || accCmd[i] == "l"){
                cpyLoadAvg();
                sendto(udp_socket, &sendBuf, sizeof(sendBuf), 0, (sockaddr*) &sother, sother_len);
                return true;
            }
        }
    }
    return false;
}

int udp_serv::cpyLoadAvg(){
    int fd = open("/proc/loadavg", O_RDONLY);
    int readBytes = read(fd, &sendBuf, sizeof(sendBuf));
    if(readBytes < 0){
        perror("Couldn't read from loadavg\n");
        return -1;
    }
    close(fd);
    return 0;
}


int udp_serv::cpyUptime(){
    int fd = open("/proc/uptime", O_RDONLY);
    int readBytes = read(fd, &sendBuf, sizeof(sendBuf));
    if(readBytes < 0){
        perror("Couldn't read from proc\n");
        return -1;
    }
    close(fd);
    return 0;
}

void udp_serv::clearBufs(){
    memset(&recvBuf, 0, sizeof(recvBuf));
    memset(&sendBuf, 0, sizeof(sendBuf));
}

int udp_serv::setup_serv(){
    // Assign address family
    // Convert ip to appropriate format

    inet_aton("10.0.0.1", &sthis.sin_addr);
    sthis.sin_family = AF_INET;
    sthis.sin_port = htons(port);


    // Must initialize this address! For some bloody reason!
    sother_len = sizeof(sother);

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

