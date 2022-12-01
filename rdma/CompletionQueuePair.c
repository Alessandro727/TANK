#include "CompletionQueuePair.h"

#define MAX_VALUE 18446744073709551615u;

CompletionQueuePair createCompletionQueuePair(struct ibv_context* context) {

	CompletionQueuePair cqp;

	cqp.completionVector = 0;

    cqp.cq_size = 2097151;

	cqp.contextPtr = NULL;

	cqp.channel = ibv_create_comp_channel(context);

	cqp.sendQueue = ibv_create_cq(context, cqp.cq_size, cqp.contextPtr, cqp.channel, cqp.completionVector);
	cqp.receiveQueue = ibv_create_cq(context, cqp.cq_size, cqp.contextPtr, cqp.channel, cqp.completionVector);

	cqp.eventsToAck = vector_create();


	int status = ibv_req_notify_cq(cqp.sendQueue,0);
	if (status != 0) {
		
		printf("Error, ibv_req_notify_cq() failed when avoiding a "
		"notification for the next completion on sendQueue\n");
		exit(EXIT_FAILURE);
	}
	status = ibv_req_notify_cq(cqp.receiveQueue,0);
	if (status != 0) {
		
		printf("Error, ibv_req_notify_cq() failed when avoiding a "
		"notification for the next completion on receiveQueue\n");
		exit(EXIT_FAILURE);
	}

	return cqp;
}

void destroyCompletionQueuePair(CompletionQueuePair cqp) {

	int num_items = vector_size(cqp.eventsToAck);

	for (int i = 0; i < num_items; i ++) {

		ibv_ack_cq_events(&(cqp.eventsToAck[i]),1);
	}

}

// Poll a completion queue
uint64_t pollCompletionQueue(struct ibv_cq* completionQueue, enum ibv_wc_opcode type) {

	struct ibv_wc wc;	
	// Poll for a work completion
	if (ibv_poll_cq(completionQueue, 1, &wc) == 0) {

		return MAX_VALUE;
	}

	// Check status and opcode
	if (wc.status != IBV_WC_SUCCESS) {
		
		printf("unexpected completion status: %d", wc.status);
		exit(EXIT_FAILURE);
	}
	if (wc.opcode != type) {
		
		printf("unexpected completion opcode: %d", wc.opcode);
		exit(EXIT_FAILURE);
	}
	return wc.wr_id;
}

// Poll the send completion queue
uint64_t pollSendCompletionQueue(CompletionQueuePair cqp) {
    // Poll for a work completion
    struct ibv_wc wc;
    if (ibv_poll_cq(cqp.sendQueue, 1, &wc) == 0) {

        return MAX_VALUE;
    }
    // Check status and opcode
    if (wc.status != IBV_WC_SUCCESS) {
        printf("unexpected completion status: %d", wc.status);
		exit(EXIT_FAILURE);
    }
    return wc.wr_id;
}

uint64_t pollSendCompletionQueue_w_opcode(CompletionQueuePair cqp, enum ibv_wc_opcode type) {
    return pollCompletionQueue(cqp.sendQueue, type);
}

// Poll the receive completion queue
uint64_t pollRecvCompletionQueue(CompletionQueuePair cqp) {
    return pollCompletionQueue(cqp.receiveQueue, IBV_WC_RECV);
}

/// Poll a completion queue blocking
uint64_t pollCompletionQueueBlocking(struct ibv_cq* completionQueue, enum ibv_wc_opcode type) {
    // Poll for a work completion
    struct ibv_wc wc;
    while (ibv_poll_cq(completionQueue, 1, &wc) == 0); // busy poll

    // Check status and opcode
	if (wc.status != IBV_WC_SUCCESS) {
		
		printf("unexpected completion status: %d", wc.status);
		exit(EXIT_FAILURE);
	}
	if (wc.opcode != type) {
		
		printf("unexpected completion opcode: %d", wc.opcode);
		exit(EXIT_FAILURE);
	}
	return wc.wr_id;
}

/// Poll the send completion queue blocking
uint64_t pollSendCompletionQueueBlocking(CompletionQueuePair cqp, enum ibv_wc_opcode opcode) {
    return pollCompletionQueueBlocking(cqp.sendQueue, opcode);
}

/// Poll the receive completion queue blocking
uint64_t pollRecvCompletionQueueBlocking(CompletionQueuePair cqp, enum ibv_wc_opcode opcode) {
    return pollCompletionQueueBlocking(cqp.receiveQueue, opcode);
}


/// Wait for a work completion
void waitForCompletion(CompletionQueuePair cqp) {
    // Wait for completion queue event

	struct ibv_cq *ev_cq;
	void *ev_ctx;
	int ret;

	ret = ibv_get_cq_event(cqp.channel, &ev_cq, &ev_ctx);
	if (ret) {
		fprintf(stderr, "Failed to get CQ event\n");
		exit(EXIT_FAILURE);
	}

    // Request a completion queue event
    int status = ibv_req_notify_cq(ev_cq, false);

    //printf("STATUS \n");

	if (status != 0) {
		printf("Error, ibv_req_notify_cq() failed when avoiding a "
		"notification for the next completion on ev_cq\n");
		exit(EXIT_FAILURE);
	}

    // Poll all work completions
    for (;;) {

    	struct ibv_wc wc;
        int numPolled = ibv_poll_cq(ev_cq, 1, &wc);

        if (numPolled == 0) {
            break;
        }
        if (numPolled < 0) {
                fprintf(stderr, "Failed to poll completions from the CQ: ret = %d\n",
                        numPolled);
                exit(EXIT_FAILURE);
        }
        if (wc.status != IBV_WC_SUCCESS) {
        	
            printf("unexpected completion status: %d\n", wc.status);
            exit(EXIT_FAILURE);
        }
    }
}

struct ibv_cq* getSendQueue(CompletionQueuePair cqp) {
    return cqp.sendQueue;
}

struct ibv_cq* getReceiveQueue(CompletionQueuePair cqp) {
    return cqp.receiveQueue;
}


static struct ibv_wc pollQueueBlocking(struct ibv_cq* queue) {
    struct ibv_wc wc;
    while (ibv_poll_cq(queue, 1, &wc) == 0); // busy poll
    if (!&wc) {
    	
        printf("unexpected completion status: %d", wc.status);
        exit(EXIT_FAILURE);
    }
    return wc;
}

struct ibv_wc pollSendWorkCompletionBlocking(CompletionQueuePair cqp) {
    return pollQueueBlocking(cqp.sendQueue);
}

struct ibv_wc pollRecvWorkCompletionBlocking(CompletionQueuePair cqp) {
    return pollQueueBlocking(cqp.receiveQueue);
}


