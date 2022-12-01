#ifndef ucqueuepair_h
#define ucqueuepair_h

#include "QueuePair.h"

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

typedef struct {

	QueuePair* qp;

} UcQueuePair;

UcQueuePair* createUcQueuePairNet(Network*);

UcQueuePair* createUcQueuePairNetCQP(Network*, CompletionQueuePair*);

void connectUCQP(UcQueuePair*, const Address*, uint8_t);

void connectUCQPOnlyAddress(UcQueuePair*, const Address*);


#ifdef __cplusplus
}
#endif

#endif