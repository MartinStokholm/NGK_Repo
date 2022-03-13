#include "server_udp.hpp"

int main() {
	UDP_SERVER myServ(9000);

	while(1) {
		myServ.RunServer();
	}

}
