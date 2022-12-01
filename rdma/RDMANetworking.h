#ifndef rdmanetworking_h
#define rdmanetworking_h

#include "RcQueuePair.h"
#include "Network.h"
#include "CompletionQueuePair.h"
#include <sys/socket.h>
#include <fcntl.h>

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif


typedef struct {

	Network network;
	CompletionQueuePair completionQueuePair;
	RcQueuePair rcQueuePair; 

} RDMANetworking;

typedef struct {

	unsigned int bufferKey;
	unsigned int readPosKey;
	unsigned long bufferAddress;
	unsigned long readPosAddress;

} RmrInfo;

typedef struct {

	unsigned long address;
	unsigned int rkey;

} RemoteAddress;


RDMANetworking* createRDMANetworking(int socket, char* ip);

RemoteAddress* offset(RemoteAddress*, uint64_t);

void receiveAndSetupRmr(int, RemoteAddress*, RemoteAddress*);

void sendRmrInfo(int, struct ibv_mr*, struct ibv_mr*);

void exchangeQPNAndConnect(int, Network*, RcQueuePair*);

void writeAddress(int, void*, unsigned long long);

void readAddress(int, void*, unsigned long long);


#ifdef __cplusplus
}
#endif

#endif