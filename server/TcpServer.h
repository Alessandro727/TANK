#ifndef tcptransportserver_h
#define tcptransportserver_h

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

typedef struct {

    int initialSocket_desc;
    int communicationSocket_desc;
    int rank;
    char* name;

} TcpServer;

TcpServer* createTcpServer();

TcpServer* createTcpServerWithPort(const char* port);

void writeTCPServer(TcpServer*, uint16_t*, size_t);

void readTCPServer(TcpServer*, uint16_t*, size_t);

size_t readSomeTCPServer(TcpServer*, uint8_t *buffer, size_t);

void acceptFromTCPServer(TcpServer*);

int acceptTCPLoop(int);

#endif



