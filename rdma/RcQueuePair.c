#include "RcQueuePair.h"

RcQueuePair* createRcQueuePairNet(Network* net) {

	RcQueuePair* rcqp = (RcQueuePair*) malloc(sizeof(RcQueuePair));
	rcqp->qp = createQueuePairNetType(net, IBV_QPT_RC);

	return rcqp;
}


RcQueuePair* createRcQueuePairNetCQP(Network* net, CompletionQueuePair* cqp) {

	RcQueuePair* rcqp = (RcQueuePair*) malloc(sizeof(RcQueuePair));
	rcqp->qp = createQueuePairNetTypeCQP(net, IBV_QPT_RC, cqp);

	return rcqp;
}


void connectRCQP(RcQueuePair* rcqp, const Address* address, uint8_t port, uint8_t retryCount) {

	struct ibv_qp_attr attr;
	memset(&attr, 0, sizeof(attr));

	attr.qp_state        = IBV_QPS_INIT;
	// Partition the queue pair belongs to
	attr.pkey_index      = 0;
	// The local physical port
	attr.port_num        = port;

	int mask = 0 | IBV_ACCESS_REMOTE_WRITE | IBV_ACCESS_REMOTE_READ | IBV_ACCESS_REMOTE_ATOMIC;
	// Allowed access flags of the remote operations for incoming packets (i.e., none, RDMA read, RDMA write, or atomics)
	attr.qp_access_flags = mask;

	if (ibv_modify_qp(rcqp->qp->queuePair, &attr,
		  	IBV_QP_STATE      |
		  	IBV_QP_PKEY_INDEX |
		  	IBV_QP_PORT       |
		  	IBV_QP_ACCESS_FLAGS)) {
		
		printf("Failed to modify QP to INIT\n");
		exit(EXIT_FAILURE);
	}

	//struct ibv_qp_attr attr;
	memset(&attr, 0, sizeof(attr));

	attr.qp_state			= IBV_QPS_RTR;
	// Maximum payload size
	attr.path_mtu			= IBV_MTU_4096;
	// The remote QP number
	attr.dest_qp_num		= address->qpn;
	// The packet sequence number of received packets
	attr.rq_psn				= 0;
	// The number of outstanding RDMA reads & atomic operations (destination)
	attr.max_dest_rd_atomic	= 16;
	// The time before a RNR NACK is sent
	attr.min_rnr_timer		= 12;


	// Whether there is a global routing header
	attr.ah_attr.is_global	   	= (uint8_t) 0;
	// The LID of the remote host
	attr.ah_attr.dlid	   		= address->lid;
	// The service level (which determines the virtual lane)
	attr.ah_attr.sl		   		= 0;
	// Use the port base LID
	attr.ah_attr.src_path_bits 	= 0;
	// The local physical port
	attr.ah_attr.port_num	   	= port;
 
 	if (address->gid.global.interface_id) {
 		attr.ah_attr.is_global	   	= (uint8_t) 1;
 		struct ibv_global_route groute;
 		memset(&groute, 0, sizeof(groute));
 		groute.hop_limit 	= 1;
 		groute.dgid			= address->gid;
 		attr.ah_attr.grh	= groute;
 	}

 	if (ibv_modify_qp(rcqp->qp->queuePair, &attr,
		  	IBV_QP_STATE              |
		  	IBV_QP_AV                 |
		  	IBV_QP_PATH_MTU           |
		  	IBV_QP_DEST_QPN           |
		  	IBV_QP_RQ_PSN             |
		  	IBV_QP_MAX_DEST_RD_ATOMIC |
		  	IBV_QP_MIN_RNR_TIMER)) {
 		
		printf("Failed to modify QP to RTR\n");
		exit(EXIT_FAILURE);
	}

	//struct ibv_qp_attr attr;
	memset(&attr, 0, sizeof(attr));
 
	attr.qp_state	    = IBV_QPS_RTS;
	// The packet sequence number of sent packets	
	attr.sq_psn	    	= 0;
	// The minimum timeout before retransmitting the packet (0 = infinite)
	attr.timeout	    = 0;
	// How often to retry sending (7 = infinite)
	attr.retry_cnt	    = retryCount;
	// How often to retry sending when RNR NACK was received (7 = infinite)
	attr.rnr_retry	    = retryCount; /* infinite */
	// The number of outstanding RDMA reads & atomic operations (initiator)
	attr.max_rd_atomic  = 16;
 
	if (ibv_modify_qp(rcqp->qp->queuePair, &attr,
		  	IBV_QP_STATE              |
		  	IBV_QP_TIMEOUT            |
		  	IBV_QP_RETRY_CNT          |
		  	IBV_QP_RNR_RETRY          |
		  	IBV_QP_SQ_PSN             |
		  	IBV_QP_MAX_QP_RD_ATOMIC)) {
		
		printf("Failed to modify QP to RTS\n");
		exit(EXIT_FAILURE);
	}

}

void connectRCQPOnlyAddress(RcQueuePair* rcqp, const Address* address) {
	connectRCQP(rcqp, address, rcqp->qp->defaultPort, 0);
}