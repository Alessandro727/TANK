#include "UcQueuePair.h"

UcQueuePair* createUcQueuePairNet(Network* net) {

	UcQueuePair* ucqp = (UcQueuePair*) malloc(sizeof(UcQueuePair));
	ucqp->qp = createQueuePairNetType(net, IBV_QPT_UC);

	return ucqp;
}

UcQueuePair* createUcQueuePairNetCQP(Network* net, CompletionQueuePair* cqp) {

	UcQueuePair* ucqp = (UcQueuePair*) malloc(sizeof(UcQueuePair));
	ucqp->qp = createQueuePairNetTypeCQP(net, IBV_QPT_UC, cqp);

	return ucqp;
}

void connectUCQP(UcQueuePair* ucqp, const Address* address, uint8_t port) {

	struct ibv_qp_attr attr;
	memset(&attr, 0, sizeof(attr));

	attr.qp_state        = IBV_QPS_INIT;
	// Partition the queue pair belongs to
	attr.pkey_index      = 0;
	// The local physical port
	attr.port_num        = port;

	int mask = IBV_ACCESS_REMOTE_WRITE;
	// Allowed access flags of the remote operations for incoming packets (i.e., none, RDMA read, RDMA write, or atomics)
	attr.qp_access_flags = mask;

	if (ibv_modify_qp(ucqp->qp->queuePair, &attr,
		  	IBV_QP_STATE      |
		  	IBV_QP_PKEY_INDEX |
		  	IBV_QP_PORT       |
		  	IBV_QP_ACCESS_FLAGS)) {
		
		printf("Failed to modify QP to INIT\n");
		exit(EXIT_FAILURE);
	}


	memset(&attr, 0, sizeof(attr));

	attr.qp_state			= IBV_QPS_RTR;
	// Maximum payload size
	attr.path_mtu			= IBV_MTU_4096;
	// The remote QP number
	attr.dest_qp_num		= address->qpn;
	// The packet sequence number of received packets
	attr.rq_psn				= 0;


	// Whether there is a global routing header
	attr.ah_attr.is_global	   	= 0;
	// The LID of the remote host
	attr.ah_attr.dlid	   		= address->lid;
	// The service level (which determines the virtual lane)
	attr.ah_attr.sl		   		= 0;
	// Use the port base LID
	attr.ah_attr.src_path_bits 	= 0;
	// The local physical port
	attr.ah_attr.port_num	   	= port;


 	if (ibv_modify_qp(ucqp->qp->queuePair, &attr,
		  	IBV_QP_STATE              |
		  	IBV_QP_AV                 |
		  	IBV_QP_PATH_MTU           |
		  	IBV_QP_DEST_QPN           |
		  	IBV_QP_RQ_PSN)) {
 		
		printf("Failed to modify QP to RTR\n");
		exit(EXIT_FAILURE);
	}


	memset(&attr, 0, sizeof(attr));
 
	attr.qp_state	    = IBV_QPS_RTS;
	// The packet sequence number of sent packets	
	attr.sq_psn	    	= 0;
	// The minimum timeout before retransmitting the packet (0 = infinite)
 
	if (ibv_modify_qp(ucqp->qp->queuePair, &attr,
		  	IBV_QP_STATE              |
		  	IBV_QP_SQ_PSN)) {
		
		printf("Failed to modify QP to RTS\n");
		exit(EXIT_FAILURE);
	}

}

void connectUCQPOnlyAddress(UcQueuePair* ucqp, const Address* address) {
    connectUCQP(ucqp, address, ucqp->qp->defaultPort);
}