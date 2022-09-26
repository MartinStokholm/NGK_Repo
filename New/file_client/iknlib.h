#ifndef LIB_H
#define LIB_H

#define PORT 9000
#define BUFSIZE 1000

#ifdef __cplusplus
    extern "C" {
#endif

void readTextTCP(int inSocket, char* text, int maxLength);
void writeTextTCP(int outSocket, const char* text);
long readFileSizeTCP(int inSocket);
const char* extractFileName(const char* text);
long getFilesize(const char* fileName);

#ifdef __cplusplus
    }
#endif

#endif // LIB_H
