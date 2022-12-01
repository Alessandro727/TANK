#include "RdmaClient.h"

#define mymin(a,b) fmin(a,b)


RdmaClient* createRDMAClient() {

    RdmaClient* rdmaClient = (RdmaClient*) malloc(sizeof(RdmaClient));

	int socket_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

	rdmaClient->socket = socket_fd;

	return rdmaClient;
}

RdmaClient* createRDMAClientWithSocket(int socket, char* ip) {

    RdmaClient* rdmaClient = (RdmaClient*) malloc(sizeof(RdmaClient));

	rdmaClient->socket = socket;

	rdmaClient->rdmaBuffer = createVirtualRDMARingBuffer(RDMA_BUFFER_SIZE, rdmaClient->socket, ip);

	return rdmaClient;
}

void connectFromRDMAClient(RdmaClient* rdmaClient, char* ip, char* port) {

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(strtol(port, NULL, 10));

    inet_pton(AF_INET, ip, &address.sin_addr);

    for (int i = 0;; ++i) {
        int v = connect(rdmaClient->socket, (struct sockaddr *)(&address), sizeof address);
        if (v == 0) {
                break;
        }
    }

    rdmaClient->rdmaBuffer = createVirtualRDMARingBuffer(RDMA_BUFFER_SIZE, rdmaClient->socket, ip);
}

void writeRDMAClient(RdmaClient* rdmaClient, void* data, unsigned long long size) {

    for (unsigned long long  i = 0; i < size;) {
	      unsigned long long chunk = mymin(size - i, RDMA_BUFFER_SIZE - 2 * sizeof(unsigned long long));
          sendRDMARingBuffer(rdmaClient->rdmaBuffer, (data + i), chunk);
          i += chunk;
   	}
}

unsigned long long readRDMAClient(RdmaClient* rdmaClient, void* buffer, unsigned long long size) {

    unsigned long long alreadyRead = 0;

    while(alreadyRead < size) {

        unsigned long long chunk = mymin(size - alreadyRead, RDMA_BUFFER_SIZE - 2 * sizeof(unsigned long long));

        unsigned long long res = receiveRDMARingBuffer(rdmaClient->rdmaBuffer, (char*) (buffer + alreadyRead), chunk);

        alreadyRead += res;

    }
    return alreadyRead;

}

unsigned long long readSomeRDMAClient(RdmaClient* rdmaClient, void* buffer, unsigned long long size) {

      unsigned long long chunk = mymin(size, RDMA_BUFFER_SIZE);
    
      unsigned long long  res = receiveRDMARingBuffer(rdmaClient->rdmaBuffer, (char*) buffer, chunk);

      return res;
}
