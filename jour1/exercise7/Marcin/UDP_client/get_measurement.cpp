#include "udp_client.h"

int main(int argc, char* argv[]){
    if(argc != 3){
        std::cout << "Usage: 'get_measurement <dest_IP> <CMD>\n";
        std::cout << "CMD: 'U' - get uptime , 'L' - get load average\n";
        return -1;
    }
    udp_client client(argv[1], argv[2]);
    client.run_client();
    return 0;
}