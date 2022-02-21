#ifndef LIB_H
#define LIB_H

#define PORT 9000
#define BUFSIZE 1000

#ifdef __cplusplus
    extern "C" {
#endif

void error(const char* msg);
const char* extractFileName(const char* fileName);
const char* readTextTCP(char* text, int length, int inFromServer);
void writeTextTCP(int outToServer, char* line);
long getFileSizeTCP(int inFromServer);
long check_File_Exists(char* fileName);

#ifdef __cplusplus
    }
#endif

#endif // LIB_H
