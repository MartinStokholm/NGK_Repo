// File handling - the C way
// Michael Alrøe
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFSIZE 20

int main ()
{
	char fileName[]	= "test.bin";
	uint8_t Buffer[BUFSIZE];
	size_t num;
	FILE * fp;

	// Generate test data
	for (int i=0; i<BUFSIZE; i++) {
		Buffer[i]=i;
	}
	for (int i=0; i<BUFSIZE; i++) printf("%i ", Buffer[i]);
	printf("\n");
	
    //*** Write file demo ***
	fp = fopen(fileName, "wb");   // write binary
	fwrite(Buffer, 1, BUFSIZE, fp);
	fclose(fp);
	
    bzero(Buffer, BUFSIZE);  // Not needed - just for test!!!
	
    //*** Read file demo ***
	fp = fopen(fileName, "rb");   // read binary
	fread(Buffer, 1, BUFSIZE, fp);  // Automatic seek!
	fclose(fp);

	for (int i=0; i<BUFSIZE; i++) printf("%i ", Buffer[i]);
	printf("\n");

	return (0);
}
