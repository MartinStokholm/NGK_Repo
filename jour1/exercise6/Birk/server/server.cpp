#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_LENGTH 256

void error(char *msg){
	perror(msg);
	exit(1);
}

// *************Set up server socket *************************
int set_up_server_socket(sockaddr_in &serv_addr, int portno)
{
	int sockfd  = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR:opening socket\n");
	
	// sets the server addrs to zeros before asignment
	bzero((char*) &serv_addr, sizeof(serv_addr));
	// 
	serv_addr.sin_family  = AF_INET;
	// check all perrifials 
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	//
	serv_addr.sin_port = htons(portno);
	// binding 
	if (bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding\n");
	//liseningo
	listen(sockfd,5);
	return sockfd;
}

// ************* Handle connected stocket **************
int accept_socket(int sockfd, struct sockaddr* cli_addr, socklen_t *clilen)
{
	int client_sockfd; 

	client_sockfd = accept(sockfd, cli_addr, clilen);
	if (client_sockfd < 0)
		error("ERROR: on accept\n");
	return client_sockfd;
}

const char * read_from_accpeted_socket(int client_sockfd, int &len)
{
	int n;
	char buffer[BUFFER_LENGTH];
	bzero(buffer,BUFFER_LENGTH);
	n = read(client_sockfd,buffer,BUFFER_LENGTH);
	if (n < 0)
		error("ERROR: on read\n");
	printf("server recived msg :%s\n", buffer);

	len = sizeof(buffer); 
	return buffer; 
}

void write_to_accepted_socket(int client_sockfd, const char * msg, int len)
{
	int n;
	n = write (client_sockfd, msg, len);
	if (n < 0) 
		error("ERROR: on write!\n");	
}	

int close_accpeted_socket(int client_sockfd)
{
	close(client_sockfd);
}


int main(int argc, char* argv[])
{

	int server_sockfd; // file descriptors for socket 
	int client_sockfd; // file descriptors for new socket.. 
	// they hold the data returned from system calls.. 
	int portno; // holds the port number

	socklen_t clilen; // holds the length of the client something
	// time for network  addresses 
	struct sockaddr_in serv_addr, cli_addr;
	
	if (argc < 2)
		fprintf(stderr,"ERROR: no port provided");
	portno = atoi(argv[1]);

	server_sockfd = set_up_server_socket(serv_addr, portno);

	int len_of_recived_msg; 
	const char *recived_msg;

	do 
	{
		clilen = sizeof(cli_addr);
		//accpeting socket from client,
		client_sockfd = accept_socket(server_sockfd,(struct sockaddr*) &cli_addr, &clilen);
		// reading from accpeted socket
		recived_msg = read_from_accpeted_socket(client_sockfd, len_of_recived_msg);
		// send ansewr to connected socket 
		write_to_accepted_socket(client_sockfd,"msg resived\n\0",strlen("msg resived\n\0"));
		// close it after its has been handel
		close_accpeted_socket(client_sockfd);

	} while (recived_msg != "close\n\0");
	close(server_sockfd);

	return 0;
}
