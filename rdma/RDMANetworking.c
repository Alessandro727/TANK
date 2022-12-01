#include "RDMANetworking.h"
#include "Network.h"

RDMANetworking* createRDMANetworking(int socket, char* ip) {

	RDMANetworking* RDMAnet = (RDMANetworking*) malloc(sizeof(RDMANetworking));

	Network* net = createNetwork(ip);

	RDMAnet->network = *net;

	RDMAnet->completionQueuePair = newCompletionQueuePair(&RDMAnet->network);

	RDMAnet->rcQueuePair = *createRcQueuePairNetCQP(&RDMAnet->network, &RDMAnet->completionQueuePair);

	int opts = fcntl(socket, F_GETFL);
    opts &= ~O_NONBLOCK;
    fcntl(socket, F_SETFL, opts);

    exchangeQPNAndConnect(socket, &RDMAnet->network, &RDMAnet->rcQueuePair);

    return RDMAnet;
}


void exchangeQPNAndConnect(int socket, Network* net, RcQueuePair* queuePair) {

	Address* address = (Address*) malloc(sizeof(Address));

	address->gid = getGID(net);

	address->lid = getLID(net);

	address->qpn  = getQPN(queuePair->qp);

    writeAddress(socket, address, sizeof(Address));
	readAddress(socket, address, sizeof(Address));

	connectRCQPOnlyAddress(queuePair, address);
}

void writeAddress(int socket, void* buffer, unsigned long long size) {

	for (unsigned long long current = 0; size > 0;) {

		int res = 0;
		while(true) {

			res = send(socket, buffer + current, size, 0);
			if (res < 0) {
				printf("Couldn't write to socket: %s\n", strerror(errno));
				//exit(EXIT_FAILURE);
			} else {
				break;
			}
		}
		current += res;
		size -= res;
	}
}

void readAddress(int socket, void* buffer, unsigned long long size) {

	for (unsigned long long current = 0; size > 0;) {
		int res;
		while(true) {
			res = recv(socket, ((char*)buffer) + current, size, 0);
			if (res >= 0) {
				break;
			}
		}
		if (res == size) {
            return;
        }
        
		current += res;
		size -= res;
	}
}

void receiveAndSetupRmr(int socket, RemoteAddress* buffer, RemoteAddress* readPos) {

	RmrInfo rmrInfo;

	readAddress(socket, &rmrInfo, sizeof(rmrInfo));

	buffer->rkey 	= rmrInfo.bufferKey;

	buffer->address = rmrInfo.bufferAddress;

	readPos->rkey    = rmrInfo.readPosKey;
	readPos->address = rmrInfo.readPosAddress;
}

void sendRmrInfo(int socket, struct ibv_mr* buffer, struct ibv_mr* readPos) {

	RmrInfo rmrInfo;

	rmrInfo.bufferKey = buffer->rkey;

	rmrInfo.bufferAddress 	= (unsigned long) buffer->addr;

	rmrInfo.readPosKey = readPos->rkey;

	rmrInfo.readPosAddress	= (unsigned long) readPos->addr;

	writeAddress(socket, &rmrInfo, sizeof(rmrInfo));
}


RemoteAddress* offset(RemoteAddress* ra, uint64_t offset) {

	ra->address = ra->address + offset;

	return ra;

}
