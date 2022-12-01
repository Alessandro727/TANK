#ifndef udqueuepair_h
#define udqueuepair_h

#include "QueuePair.h"

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

typedef struct {

	QueuePair* qp;

} UdQueuePair;

UdQueuePair* createUdQueuePairNet(Network*);

void connectUDQP(UdQueuePair*, uint8_t, uint32_t);

void connectUDQPDef(UdQueuePair*);


#ifdef __cplusplus
}
#endif

#endif