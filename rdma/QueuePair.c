#include "QueuePair.h"

QueuePair* createQueuePair(Network* net, enum ibv_qp_type type, CompletionQueuePair* cqp, struct ibv_srq* receiveQueue) {

	QueuePair* qp = (QueuePair*) malloc(sizeof(QueuePair));

	qp->defaultPort = net->ibport;

	qp->maxOutstandingSendWrs = 8192;
        //qp->maxOutstandingSendWrs = 4096;
	//qp->maxOutstandingRecvWrs = 4096;
	qp->maxOutstandingRecvWrs = 32768;

	qp->maxSlicesPerSendWr = 4;
	qp->maxSlicesPerRecvWr = 1;

	qp->maxInlineSize   = 32;
	qp->signalAll 		= 0;

	qp->receiveQueue = receiveQueue;

	struct ibv_qp_init_attr qp_init_attr;
	//memset(&qp_init_attr, 0, sizeof(qp_init_attr));


	qp_init_attr.qp_context = qp->context;
	
	qp_init_attr.send_cq = getSendQueue(*cqp);
	qp_init_attr.recv_cq = getReceiveQueue(*cqp);

	qp_init_attr.srq = receiveQueue;

	qp_init_attr.cap.max_send_wr  = qp->maxOutstandingSendWrs;
	qp_init_attr.cap.max_recv_wr  = qp->maxOutstandingRecvWrs;
	qp_init_attr.cap.max_send_sge = qp->maxSlicesPerSendWr;
	qp_init_attr.cap.max_recv_sge = qp->maxSlicesPerRecvWr;

	qp_init_attr.cap.max_inline_data = qp->maxInlineSize;

	qp_init_attr.qp_type = type;

	qp_init_attr.sq_sig_all = 0;

	qp->queuePair = ibv_create_qp(net->protectionDomain, &qp_init_attr);

	return qp;

}

QueuePair* createQueuePairNetType(Network* net, enum ibv_qp_type type) {
	return createQueuePair(net, type, &(net->sharedCompletionQueuePair), net->sharedReceiveQueue);
}

QueuePair* createQueuePairNetTypeCQP(Network* net, enum ibv_qp_type type, CompletionQueuePair* cqp) {
	return createQueuePair(net, type, cqp, net->sharedReceiveQueue);
}

QueuePair* createQueuePairNetTypeSRQ(Network* net, enum ibv_qp_type type, struct ibv_srq* receiveQueue) {
	return createQueuePair(net, type, &(net->sharedCompletionQueuePair), receiveQueue);
}

uint32_t getQPN(QueuePair* qp) {
	return qp->queuePair->qp_num;
}

void postWorkRequest(QueuePair* qp, struct ibv_send_wr *wr) {
    struct ibv_send_wr **bad_wr;
    if (ibv_post_send(qp->queuePair, wr, bad_wr)) {
    	
		printf("Error, ibv_post_send() failed\n");
		exit(EXIT_FAILURE);
	}
}

void postRecvRequest(QueuePair* qp, struct ibv_recv_wr *wr) {
    struct ibv_recv_wr **bad_wr;
    if (ibv_post_srq_recv(qp->receiveQueue, wr, bad_wr)) {
    	
		printf("Error, ibv_post_recv() failed\n");
		exit(EXIT_FAILURE);
	}
}

uint32_t getMaxInlineSize(QueuePair* qp) {
	return qp->maxInlineSize;
}
