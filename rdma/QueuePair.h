#ifndef queuepair_h
#define queuepair_h

#include <infiniband/verbs.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Network.h"

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif


struct QueuePair {

	// Associated context of the QP (returned in completion events)
	void *context;
	
	// Max number of outstanding WRs in the SQ
	uint32_t maxOutstandingSendWrs;
	
	// Max number of outstanding WRs in the RQ
	uint32_t maxOutstandingRecvWrs;
	
	// Max number of scatter/gather elements in a WR in the SQ
	uint32_t maxSlicesPerSendWr;
	
	// max number of scatter/gather elements in a WR in the RQ
	uint32_t maxSlicesPerRecvWr;
	
	// max number of bytes that can be posted inline to the SQ
	uint32_t maxInlineSize;
	
	// If each Work Request (WR) submitted to the SQ generates a completion entry
	int signalAll;

	uint8_t defaultPort;

	struct ibv_qp* queuePair;

	struct ibv_srq* receiveQueue;

};

typedef struct QueuePair QueuePair;

QueuePair* createQueuePair(Network *, enum ibv_qp_type, CompletionQueuePair*, struct ibv_srq*);

QueuePair* createQueuePairNetType(Network *, enum ibv_qp_type);

QueuePair* createQueuePairNetTypeCQP(Network *, enum ibv_qp_type, CompletionQueuePair*);

QueuePair* createQueuePairNetTypeSRQ(Network *, enum ibv_qp_type, struct ibv_srq*);

uint32_t getQPN(QueuePair*);

void postWorkRequest(QueuePair*, struct ibv_send_wr*);

void postRecvRequest(QueuePair*, struct ibv_recv_wr*);

uint32_t getMaxInlineSize(QueuePair*);


#ifdef __cplusplus
}
#endif

#endif
