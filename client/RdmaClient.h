#ifndef rdmatransportclient_h
#define rdmatransportclient_h

#include "../buffers/VirtualRDMARingBuffer.h"
#include <sys/socket.h>
#include <math.h>
#include <arpa/inet.h>


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
	VirtualRDMARingBuffer* rdmaBuffer;

} RdmaClient;

RdmaClient* createRDMAClient();

RdmaClient* createRDMAClientWithSocket(int, char*);

void connectFromRDMAClient(RdmaClient*, char*, char*);

void writeRDMAClient(RdmaClient*, void*, unsigned long long);

unsigned long long readRDMAClient(RdmaClient*, void*, unsigned long long);

unsigned long long readSomeRDMAClient(RdmaClient*, void*, unsigned long long);

#ifdef __cplusplus
}
#endif

#endif
