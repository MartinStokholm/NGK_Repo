// File handling - the stream way
// Michael Alrøe

#include <iostream>
#include <fstream>
#include <string.h>

#define BUFSIZE 20

using namespace std;

int main(){
	uint8_t Buffer[BUFSIZE];
	string fileName = "stream.bin";

	// Generate test data
	for (int i=0; i<BUFSIZE; i++) {
		Buffer[i]=i;
	}
	for (int i=0; i< BUFSIZE; i++){
		cout << to_string(Buffer[i]) << " ";
	}
	cout << endl;

	//*** Write file demo ***
	ofstream file_fw(fileName, std::ios::binary);  // Define output stream
	file_fw.write((char*)Buffer, BUFSIZE);
	file_fw.close();
	
    bzero(Buffer, BUFSIZE);  // Not needed - just for test!!!
	
    //*** Read file demo ***
	ifstream file_fr(fileName, std::ios::binary);  // Define input stream
	file_fr.read((char*)Buffer, BUFSIZE);  // Automatic seek!
	file_fr.close();
	
    for (int i=0; i< BUFSIZE; i++){
		cout << to_string(Buffer[i]) << " ";
	}
	cout << endl;

    return (0);
}