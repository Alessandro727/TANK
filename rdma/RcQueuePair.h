#ifndef rcqueuepair_h
#define rcqueuepair_h

#include "QueuePair.h"

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

typedef struct {

	QueuePair* qp;

} RcQueuePair;

RcQueuePair* createRcQueuePairNet(Network*);

RcQueuePair* createRcQueuePairNetCQP(Network*, CompletionQueuePair*);

void connectRCQP(RcQueuePair*, const Address*, uint8_t, uint8_t);

void connectRCQPOnlyAddress(RcQueuePair*, const Address*);


#ifdef __cplusplus
}
#endif

#endif