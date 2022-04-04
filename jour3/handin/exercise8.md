# Exercise 8 Transpport Layer - UDP Client/Server, TCP Client/Server

## UDP-Client/Server
In this exercise we will examine communication between a UDP client and server using wireshark. 
First we start the UDP-server and client in there own machines H1 as the server and H2 as the client. 

![](../handin/screenshots/ex8/netcat_udp_client.jpg)

![](screenshots/ex8/netcat_udp_server.jpg)

As you can see form the screen shots above we have already sent some messages back and forth. The header and payload are shown in the screenshot below.

![](screenshot/../screenshots/ex8/udp_header.jpg)

Unlike the TCP connection we do not see a opening of the connection with a three-way handshake. The same is true for closing the connection, where again we dont see anything with the UDP connection. In terms of the payload, we notice that the message is not encrypted, but just plain text. 
