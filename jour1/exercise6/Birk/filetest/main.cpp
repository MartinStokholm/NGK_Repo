#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>

int main()
{
	int n;
	char input[255];
	bzero(input, sizeof(input));
	int fd = open("./text.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); 

	printf("enter text to file\n> ");
	fgets(input, 255, stdin);

	 n =	write(fd, input, strlen(input)); 
	printf("\ninput string length is %li long, and size of is %li", strlen(input), sizeof(input));
	printf("\n%i bytes where written to file\n", n);	

	int status = close(fd);
	printf("the status of the close file was: %i", status);
	
	fd = open("./text.txt", O_RDONLY, n); 
	char buffer[n];
	n = read(fd, buffer, sizeof(buffer));
	printf("from file %i bytes where read, and the content where\n> ", n);
	printf(buffer);
	if (0 >  close(fd))
		return 1;

	return 0;

}	
