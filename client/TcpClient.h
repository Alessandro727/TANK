#ifndef tcpclient_h
#define tcpclient_h

#include "../utils/utils.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

typedef struct {

    int socket;
    int rank;
    char* name;

} TcpClient;


TcpClient* createTcpClient();

int connectFromTCPClient(TcpClient*, char*, char*);

void writeTCPClient(TcpClient*, char*, size_t);

void readTCPClient(TcpClient*, char*, size_t);

size_t readSomeTCPClient(TcpClient*, uint8_t*, size_t);



#endif
