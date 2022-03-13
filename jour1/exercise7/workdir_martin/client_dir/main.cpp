#include "client_udp.hpp"

int main() {
	 
	UDP_CLIENT  myClient(9000, "10.0.0.1", "U");

	while(1) {
		myClient.RunClient();
	}

}
