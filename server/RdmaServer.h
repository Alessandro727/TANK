#ifndef rdmaserver_h
#define rdmaserver_h

#include "../buffers/VirtualRDMARingBuffer.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <math.h>


#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif


//#define RDMA_BUFFER_SIZE 1048576
//#define RDMA_BUFFER_SIZE 2097152
//#define RDMA_BUFFER_SIZE 2097152*64
//#define RDMA_BUFFER_SIZE 1073741824
//#define RDMA_BUFFER_SIZE 2048*256
//#define RDMA_BUFFER_SIZE 2048*512
//#define RDMA_BUFFER_SIZE 2048*1024
//#define RDMA_BUFFER_SIZE 2048*2048
//#define RDMA_BUFFER_SIZE 16777216
//#define RDMA_BUFFER_SIZE 8388608
//#define RDMA_BUFFER_SIZE 4194304
#define RDMA_BUFFER_SIZE 33554432
//#define RDMA_BUFFER_SIZE 67108864
//#define RDMA_BUFFER_SIZE 134217728
//#define RDMA_BUFFER_SIZE 268435456
//#define RDMA_BUFFER_SIZE 536870912

typedef struct {

	int socket;
	int communicationSocket;
	VirtualRDMARingBuffer* rdmaBuffer;

} RdmaServer;

RdmaServer* createRDMAServer(char*, char*);

RdmaServer* createRDMAServerWithSocket(int, char*);

int openSocket(char*, char*);

void bindAndListenRDMASocket(int, const char*, char*);

void acceptFromRDMAServer(RdmaServer*, char*);

int acceptRDMALoop(int);

void writeRDMAServer(RdmaServer*, void*, unsigned long long);

unsigned long long readRDMAServer(RdmaServer*, void*, unsigned long long);

unsigned long long readSomeRDMAServer(RdmaServer*, void*, unsigned long long);

#ifdef __cplusplus
}
#endif

#endif
