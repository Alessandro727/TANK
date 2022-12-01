#include "VirtualRDMARingBuffer.h"


VirtualRDMARingBuffer* createVirtualRDMARingBuffer(unsigned long long size, int socket, char* ip) {

	bool powerOfTwo = (size != 0) && !(size & (size - 1));

    if (!powerOfTwo) {
        perror("size should be a power of 2");
	    exit(EXIT_FAILURE);
    }

	VirtualRDMARingBuffer* vRDMARingBuf = (VirtualRDMARingBuffer*) malloc(sizeof(VirtualRDMARingBuffer));

	vRDMARingBuf->validity 	= 0xDEADDEADBEEFBEEF; // arbitrary constant. Just don't use 0
	vRDMARingBuf->size 		= (const unsigned long long) size;
	vRDMARingBuf->bitmask 	= (const unsigned long long) size - 1; 

	vRDMARingBuf->messageCounter = 0;
	vRDMARingBuf->sendPos		 = 0;

	atomic_store(&(vRDMARingBuf->localReadPos), 0);

	atomic_store(&(vRDMARingBuf->remoteReadPos), 0);

	uuid_t binuuid;
    uuid_generate_random(binuuid);
    char randomUUID[37];
    uuid_unparse_lower(binuuid, randomUUID);

	vRDMARingBuf->RDMAnet = *createRDMANetworking(socket, ip);

	vRDMARingBuf->sendBuf = createCircularBuf("/RDMASendBuffer", randomUUID, size);

	uuid_t binuuid2;
    uuid_generate_random(binuuid2);
    char randomUUID2[37];
    uuid_unparse_lower(binuuid2, randomUUID2);

	vRDMARingBuf->receiveBuf = createCircularBuf("/RDMAReceiveBuffer", randomUUID2, size);

	vRDMARingBuf->localSendMr		= registerMr(vRDMARingBuf->RDMAnet.network, vRDMARingBuf->sendBuf->data, size * 2, 0);
	vRDMARingBuf->localReadPosMr 	= registerMr(vRDMARingBuf->RDMAnet.network, &(vRDMARingBuf->localReadPos), sizeof(vRDMARingBuf->localReadPos), IBV_ACCESS_REMOTE_READ);
	vRDMARingBuf->localReceiveMr	= registerMr(vRDMARingBuf->RDMAnet.network, vRDMARingBuf->receiveBuf->data, size * 2, IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_WRITE);
	vRDMARingBuf->remoteReadPosMr	= registerMr(vRDMARingBuf->RDMAnet.network, &(vRDMARingBuf->remoteReadPos), sizeof(vRDMARingBuf->remoteReadPos), IBV_ACCESS_LOCAL_WRITE);

	sendRmrInfo(socket, vRDMARingBuf->localReceiveMr, vRDMARingBuf->localReadPosMr);

	receiveAndSetupRmr(socket, &vRDMARingBuf->remoteReceiveRmr, &vRDMARingBuf->remoteReadPosRmr);

	return vRDMARingBuf;
}

unsigned long long sendRDMARingBuffer(VirtualRDMARingBuffer* rdma, void* data , unsigned long long length) {

	const unsigned long long startOfWrite = rdma->sendPos & rdma->bitmask;

	unsigned long long volatile* sizePtr = (unsigned long long volatile*) &(rdma->sendBuf->data[startOfWrite]);

	unsigned char volatile* begin = (unsigned char volatile*)(sizePtr + 1);

	memcpy(begin, data, length);
//	memmove(begin, data, length);
//	memcpy_v(begin,data,length);

	const unsigned long long dataSize = length;

	const unsigned long long sizeToWrite = sizeof(rdma->size) + dataSize + sizeof(rdma->validity);

	if (sizeToWrite > rdma->size) {
		perror("data > buffersize!");
	    exit(EXIT_FAILURE);
	}

	*sizePtr = dataSize;

	unsigned long long volatile* validityPtr = (unsigned long long volatile*)(begin + dataSize);

	*validityPtr = rdma->validity;

	struct ibv_sge sendSlice;
	memset(&sendSlice, 0, sizeof(sendSlice));

    sendSlice.addr          = ((uintptr_t)(rdma->localSendMr->addr)) + startOfWrite;

    sendSlice.length        = sizeToWrite;
	sendSlice.lkey 		= rdma->localSendMr->lkey;

	struct ibv_send_wr wr;
	memset(&wr, 0, sizeof(wr));

	wr.opcode = IBV_WR_RDMA_WRITE;
	wr.sg_list = &sendSlice;
	wr.num_sge = 1;

	wr.wr.rdma.remote_addr = rdma->remoteReceiveRmr.address + ((unsigned long long) startOfWrite);
	wr.wr.rdma.rkey        = rdma->remoteReceiveRmr.rkey;

	if (rdma->messageCounter % (4 * 1024) == 0)	{
		wr.send_flags = IBV_SEND_SIGNALED;
	}


	if (sendSlice.length <= rdma->RDMAnet.rcQueuePair.qp->maxInlineSize) {
		wr.send_flags = wr.send_flags | IBV_SEND_INLINE;
	}

	blockUntilRDMABufferFree(rdma, sizeToWrite);

	postWorkRequest(rdma->RDMAnet.rcQueuePair.qp, &wr);

	if (rdma->messageCounter % (4 * 1024) == 0)	{
		waitForCompletion(rdma->RDMAnet.completionQueuePair);
	}

	rdma->messageCounter += 1;

	rdma->sendPos += sizeToWrite;

	return sizeToWrite;
}

unsigned long long receiveRDMARingBuffer(VirtualRDMARingBuffer* rdma, void* whereTo, unsigned long long maxSize) {

	if (maxSize == -1) {
		return 0;
	}
	int pad = 0;

	const unsigned long long lastReadPos = (unsigned long long) atomic_load(&(rdma->localReadPos));

	const unsigned long long startOfRead = lastReadPos & rdma->bitmask;

	unsigned long receiveSize;
	unsigned long checkMe;

	while (checkMe != rdma->validity) {

		receiveSize = *((unsigned long volatile*)&(rdma->receiveBuf->data[startOfRead]));

		checkMe = *((unsigned long volatile*)&(rdma->receiveBuf->data[startOfRead + sizeof(unsigned long) + receiveSize]));
	}

	const unsigned char* begin = &(rdma->receiveBuf->data[startOfRead + sizeof(receiveSize)]);

	//const unsigned char* end = begin + receiveSize;

    memcpy((uint8_t*)whereTo+pad, begin, receiveSize);
    //memcpy_v(whereTo+pad, begin, receiveSize);

	const unsigned long long totalSizeRead = sizeof(receiveSize) + receiveSize + sizeof(rdma->validity);

	memset(&(rdma->receiveBuf->data[startOfRead]), 0, totalSizeRead);

	atomic_store_explicit(&(rdma->localReadPos), lastReadPos+ totalSizeRead, memory_order_release);

    return receiveSize;
}

void blockUntilRDMABufferFree(VirtualRDMARingBuffer* rdma, unsigned long long sizeToWrite) {

	atomic_ullong lastReadPos = atomic_load(&(rdma->remoteReadPos));

	unsigned long long safeToWrite = rdma->size - (rdma->sendPos - lastReadPos);

	while (safeToWrite < sizeToWrite) {

		struct ibv_send_wr wr;
		memset(&wr, 0, sizeof(wr));

		struct ibv_sge sendSlice;

		memset(&sendSlice, 0, sizeof(sendSlice));

		sendSlice.addr 	= (uintptr_t)rdma->remoteReadPosMr->addr;
		sendSlice.length 	= rdma->remoteReadPosMr->length;
		sendSlice.lkey 	= rdma->remoteReadPosMr->lkey;

		wr.sg_list = &sendSlice;
		wr.num_sge = 1;
		wr.opcode = IBV_WR_RDMA_READ;

		wr.wr.rdma.remote_addr = rdma->remoteReadPosRmr.address;
		wr.wr.rdma.rkey        = rdma->remoteReadPosRmr.rkey;

		wr.send_flags = 0 | IBV_SEND_SIGNALED;

		wr.wr_id = (unsigned long) 56;

		postWorkRequest(rdma->RDMAnet.rcQueuePair.qp, &wr);

		while(pollSendCompletionQueue(rdma->RDMAnet.completionQueuePair) != 56) {
		}

		atomic_ullong lastReadPos2 = atomic_load(&(rdma->remoteReadPos));
		safeToWrite = rdma->size - (rdma->sendPos - lastReadPos2);
	}
}

CircularBuffer* createCircularBuf(char* bufferName, char* uuid, unsigned long long size) {

	char* new_bufferName = (char*) malloc(strlen(bufferName)+1+37);

    strcpy(new_bufferName, bufferName);

    strcat(new_bufferName, uuid);

    CircularBuffer* circularBuffer = mmapLocalCircularBuffer(new_bufferName, size);

    return circularBuffer;
}

volatile void *memcpy_v(volatile void *restrict dest,
            const volatile void *restrict src, size_t n) {
    const volatile unsigned char *src_c = src;
    volatile unsigned char *dest_c      = dest;

    while (n > 0) {
        n--;
        dest_c[n] = src_c[n];
    }
    return  dest;
}

