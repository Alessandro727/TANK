#ifndef virtualrdmaringbuffer_h
#define virtualrdmaringbuffer_h

#include "../rdma/RDMANetworking.h"
#include "../utils/virtualMemory.h"
#include <uuid/uuid.h>

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif


typedef struct {

	unsigned long long validity;
	unsigned long long size;
	unsigned long long bitmask;

	RDMANetworking RDMAnet;

	unsigned long long messageCounter;
	unsigned long long sendPos;

	atomic_ullong localReadPos;
	CircularBuffer* sendBuf;
	struct ibv_mr* localSendMr;
	struct ibv_mr* localReadPosMr;

	atomic_ullong remoteReadPos;
	CircularBuffer* receiveBuf;
	struct ibv_mr* localReceiveMr;
	struct ibv_mr* remoteReadPosMr;

	RemoteAddress remoteReceiveRmr;
	RemoteAddress remoteReadPosRmr;

} VirtualRDMARingBuffer;


VirtualRDMARingBuffer* createVirtualRDMARingBuffer(unsigned long long, int, char*);

unsigned long long sendRDMARingBuffer(VirtualRDMARingBuffer*, void*, unsigned long long);

unsigned long long receiveRDMARingBuffer(VirtualRDMARingBuffer*, void*, unsigned long long);

void blockUntilRDMABufferFree(VirtualRDMARingBuffer*, unsigned long long);

CircularBuffer* createCircularBuf(char*, char*, unsigned long long);

volatile void *memcpy_v(volatile void *, const volatile void *, size_t);

#ifdef __cplusplus
}
#endif

#endif

