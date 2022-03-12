
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>

// Tasks 
// get length of file
// spilt file in 0 to 1000 bytes chunks
	// 
// get number of chunks 
// send sizeof file 
// for n in number of chunks
	// send chunk[n] 
// 




void error(const char * msg, int err_no)
{
	printf(msg);
	printf(": %i\n", err_no); 
	exit(err_no); 

}

int mail(int argc, char**argv)
{
	if (argc != 2)
		error("ERROR: use ./prog <path to file>", 1);
	char input[BUFFER_LENGTH];
	strcpy(input, argv[1]);




