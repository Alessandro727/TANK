#ifndef completionqueuepair_h
#define completionqueuepair_h

#include <stdio.h>
#include <infiniband/verbs.h>
#include <stdbool.h>
#include "../utils/vec.h"


#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//#include <rdma/rdma_cma.h>

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

struct ccpair {

	bool flag;
	uint64_t value;

};

typedef struct ccpair ccpair;

typedef struct {

	void* contextPtr;
	int completionVector;
    // The minimal number of entries for the completion queue
    int cq_size;

    // The completion channel
    struct ibv_comp_channel* channel;
    // The send completion queue
    struct ibv_cq* sendQueue;
    // The receive completion queue
    struct ibv_cq* receiveQueue;

    // The cached work completions
    struct ccpair* cachedCompletions;

    // Protect wait for events method from concurrent access
    pthread_mutex_t guard;

    struct ibv_cq* eventsToAck;

} CompletionQueuePair;

CompletionQueuePair createCompletionQueuePair(struct ibv_context*);

void destroyCompletionQueuePair(CompletionQueuePair);

uint64_t pollCompletionQueue(struct ibv_cq*, enum ibv_wc_opcode);

uint64_t pollSendCompletionQueue(CompletionQueuePair);

uint64_t pollSendCompletionQueue_w_opcode(CompletionQueuePair, enum ibv_wc_opcode);

uint64_t pollRecvCompletionQueue(CompletionQueuePair);

uint64_t pollCompletionQueueBlocking(struct ibv_cq*, enum ibv_wc_opcode);

/// Poll the send completion queue blocking
uint64_t pollSendCompletionQueueBlocking(CompletionQueuePair, enum ibv_wc_opcode);

uint64_t pollRecvCompletionQueueBlocking(CompletionQueuePair, enum ibv_wc_opcode);

void waitForCompletion(CompletionQueuePair);

struct ibv_cq* getSendQueue(CompletionQueuePair);

struct ibv_cq* getReceiveQueue(CompletionQueuePair);

static struct ibv_wc pollQueueBlocking(struct ibv_cq*);

struct ibv_wc pollSendWorkCompletionBlocking(CompletionQueuePair);

struct ibv_wc pollRecvWorkCompletionBlocking(CompletionQueuePair);


#ifdef __cplusplus
}
#endif

#endif
