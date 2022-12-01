#include "RdmaServer.h"

#define mymin(a,b) fmin(a,b)


RdmaServer* createRDMAServer(char* remoteIp, char* port) {

    RdmaServer* rdmaServer = (RdmaServer*) malloc(sizeof(RdmaServer));

	rdmaServer->socket = openSocket(remoteIp, port);

	return rdmaServer;
}

RdmaServer* createRDMAServerWithSocket(int socket, char* localip) {

    RdmaServer* rdmaServer = (RdmaServer*) malloc(sizeof(RdmaServer));

	rdmaServer->communicationSocket = socket;

	rdmaServer->rdmaBuffer= createVirtualRDMARingBuffer(RDMA_BUFFER_SIZE, rdmaServer->communicationSocket, localip);

	return rdmaServer;
}

int openSocket(char* remoteIp, char* port) {

    int socket_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    bindAndListenRDMASocket(socket_fd, remoteIp, port);
   
    return socket_fd;

}

void bindAndListenRDMASocket(int sock_desc,  const char* remoteIp, char* port) {

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = inet_addr(remoteIp);
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(strtol(port, NULL, 10));

    int optval = 1;
    setsockopt(sock_desc, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

   	if (bind(sock_desc, (struct sockaddr*)&address,
             sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
   	setsockopt(sock_desc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

   	if (listen(sock_desc, SOMAXCONN) < 0) {
        perror("Couldn't listen on socket");
        exit(EXIT_FAILURE);
    }
}


void acceptFromRDMAServer(RdmaServer* rdmaServer, char* localip) {

    int com_socket = acceptRDMALoop(rdmaServer->socket);

    rdmaServer->communicationSocket = com_socket;

	rdmaServer->rdmaBuffer = createVirtualRDMARingBuffer(RDMA_BUFFER_SIZE, rdmaServer->communicationSocket, localip);
}

int acceptRDMALoop(int socket) {
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    int com_socket;
    while ( true ) {

        addr_size = sizeof serverStorage;
        com_socket = accept4(socket, NULL, NULL, SOCK_NONBLOCK);

        if ( com_socket >= 0 ) {
            break;
        }

        if ( errno == EAGAIN || errno == EINTR || errno == ECONNABORTED) {
            continue;
        }
        else {
            perror("error accept'ing");
            printf( "Value of errno: %d\n", errno );
            exit(EXIT_FAILURE);
        }
    }
    close(socket);
    return com_socket;
}


void writeRDMAServer(RdmaServer* rdmaServer, void* data, unsigned long long size) {

	for (unsigned long long  alreadyWrite = 0; alreadyWrite < size;) {

        unsigned long long chunk = mymin(size - alreadyWrite, RDMA_BUFFER_SIZE - 2 * sizeof(unsigned long long));

        sendRDMARingBuffer(rdmaServer->rdmaBuffer, data + alreadyWrite, chunk);

        alreadyWrite += chunk;
   	}
}


unsigned long long readRDMAServer(RdmaServer* rdmaServer, void* buffer, unsigned long long size) {

    unsigned long long alreadyRead = 0;

    while(alreadyRead < size) {

        unsigned long long chunk = mymin(size - alreadyRead, RDMA_BUFFER_SIZE - 2 * sizeof(unsigned long long));

        unsigned long long res = receiveRDMARingBuffer(rdmaServer->rdmaBuffer, (char*) (buffer + alreadyRead), chunk);

        alreadyRead += res;
   	
    }
	return alreadyRead;
}

unsigned long long readSomeRDMAServer(RdmaServer* rdmaServer, void* buffer, unsigned long long size) {

    unsigned long long chunk = mymin(size, RDMA_BUFFER_SIZE);
    
    unsigned long long  res = receiveRDMARingBuffer(rdmaServer->rdmaBuffer, (char*) buffer, chunk);

    return res;
}
