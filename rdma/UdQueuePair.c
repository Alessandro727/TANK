#include "UdQueuePair.h"

#define QKEY 0x22222222;

UdQueuePair* createUdQueuePairNet(Network* net) {

	UdQueuePair* udqp = (UdQueuePair*) malloc(sizeof(UdQueuePair));
	udqp->qp = createQueuePairNetType(net, IBV_QPT_UD);

	return udqp;
}


void connectUDQP(UdQueuePair* udqp, uint8_t port, uint32_t packetSequenceNumber) {

	struct ibv_qp_attr attr;
	memset(&attr, 0, sizeof(attr));

	attr.qp_state        = IBV_QPS_INIT;
	// Partition the queue pair belongs to
	attr.pkey_index      = 0;
	// The local physical port
	attr.port_num        = port;


	attr.qkey            = QKEY;

	if (ibv_modify_qp(udqp->qp->queuePair, &attr,
		  	IBV_QP_STATE      |
		  	IBV_QP_PKEY_INDEX |
		  	IBV_QP_PORT       |
		  	IBV_QP_QKEY)) {
		printf("Failed to modify QP to INIT\n");
		exit(EXIT_FAILURE);
	}


	memset(&attr, 0, sizeof(attr));

	attr.qp_state			= IBV_QPS_RTR;


 	if (ibv_modify_qp(udqp->qp->queuePair, &attr,
		  	IBV_QP_STATE)) {
		printf("Failed to modify QP to RTR\n");
		exit(EXIT_FAILURE);
	}


	memset(&attr, 0, sizeof(attr));
 
	attr.qp_state	    = IBV_QPS_RTS;
	// The packet sequence number of sent packets	
	attr.sq_psn	    	= packetSequenceNumber;
 
	if (ibv_modify_qp(udqp->qp->queuePair, &attr,
		  	IBV_QP_STATE              |
		  	IBV_QP_SQ_PSN)) {
		
		printf("Failed to modify QP to RTS\n");
		exit(EXIT_FAILURE);
	}

}

void connectUDQPDef(UdQueuePair* udqp) {
    connectUDQP(udqp, udqp->qp->defaultPort, 0);
}