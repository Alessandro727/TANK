#include "VirtualSHMRingBuffer.h"

SHMRingBuffer* createSHMRingBuffer(unsigned long long size, char* filename)    {

    SHMRingBuffer* combuffer = (SHMRingBuffer*) malloc(sizeof(SHMRingBuffer));

    combuffer->bufferName = "/sharedBuffer";
    
    combuffer->syncFileName = "/sharedSyncFile";
    
    bool powerOfTwo = (size != 0) && !(size & (size - 1));

    if (!powerOfTwo) {
        perror("size should be a power of 2");
	    exit(EXIT_FAILURE);
    }

    combuffer->size = size; 
    
    combuffer->bitmask = size - 1;
    
    combuffer->name = filename;

    uuid_t binuuid;
    uuid_generate_random(binuuid);
    char randomUUID[37];
    uuid_unparse_lower(binuuid, randomUUID);

    char* new_syncFileName = (char*) malloc(strlen(combuffer->syncFileName)+1+37);

    strcpy(new_syncFileName, combuffer->syncFileName);
    
    strcat(new_syncFileName, randomUUID);

    combuffer->syncFile = mmapLocalSyncFile(new_syncFileName, sizeof(CircularBufferInfo), NULL);

    char* new_bufferName = (char*) malloc(strlen(combuffer->bufferName)+1+37);

    strcpy(new_bufferName, combuffer->bufferName);

    strcat(new_bufferName, randomUUID);

    combuffer->circularBuffer = mmapLocalCircularBuffer(new_bufferName, size);

    return combuffer;

}

void shareSHMRingBuffer(int communicationSocket, SHMRingBuffer* commBuffer) {

	send_fd(communicationSocket, commBuffer->syncFile->fd);

	send_fd(communicationSocket, commBuffer->circularBuffer->fd);

}

SHMRingBuffer* acquireSHMRingBuffer(int communicationSocket, unsigned long long size, char* filename) {

    SHMRingBuffer* combuffer = (SHMRingBuffer*) malloc(sizeof(SHMRingBuffer));

    combuffer->bufferName = "/sharedBuffer";
    
    combuffer->syncFileName = "/sharedSyncFile";
    
    bool powerOfTwo = (size != 0) && !(size & (size - 1));

    if (!powerOfTwo) {
        perror("size should be a power of 2");
	    exit(EXIT_FAILURE);
    }

    combuffer->size = size; 
    
    combuffer->bitmask = size - 1;
    
    combuffer->name = filename;

	int syncFileFd = receive_fd(communicationSocket);

    combuffer->syncFile = mmapRemoteSyncFile(syncFileFd, sizeof(CircularBufferInfo), NULL);

    int circularBufferFd = receive_fd(communicationSocket);

    combuffer->circularBuffer = mmapRemoteCircularBuffer(circularBufferFd, size, false);

    return combuffer;

}

unsigned long long writeSHMRingBuffer(SHMRingBuffer* cb, void *data, unsigned long long length) {

    atomic_ullong localWritten = atomic_load(&(cb->syncFile->data->written));

    unsigned long long pos = localWritten & cb->bitmask;

    blockUntilBufferFree(cb, localWritten, length);

    memcpy(&cb->circularBuffer->data[pos], data, length);

    atomic_store(&(cb->syncFile->data->written), localWritten + length);

    cb->syncFile->data->written = localWritten + length;

    return length;
}

unsigned long long receiveSHMRingBuffer(SHMRingBuffer* vrb, void *whereTo, unsigned long long maxSize) {

    atomic_ullong localRead = atomic_load(&(vrb->syncFile->data->read));

    unsigned long long pos = localRead & vrb->bitmask;

    blockUntilBufferAvailable(vrb, maxSize, localRead);

    memcpy((int*)(whereTo), &vrb->circularBuffer->data[pos], maxSize);

    atomic_store(&(vrb->syncFile->data->read), localRead + maxSize);

    return maxSize;
}

void blockUntilBufferFree(SHMRingBuffer* vrb, atomic_ullong localWritten, unsigned long long length) {

	unsigned long long cachedRead = (unsigned long long) atomic_load(&(vrb->syncFile->data->read));

	if ((localWritten - cachedRead) > (vrb->size - length)) {

        int tries = 0;

        while ((localWritten - cachedRead) > (vrb->size - length)) {

            yield(tries);

            cachedRead = (unsigned long long) atomic_load(&(vrb->syncFile->data->read));

            ++tries;
        }
    }
}

void blockUntilBufferAvailable(SHMRingBuffer* vrb, unsigned long long maxSize, atomic_ullong localRead) {

    unsigned long long remoteWritten = vrb->syncFile->data->written;

    int tries = 0;

    while ((remoteWritten - localRead) < maxSize)   {

        yield(tries);
    
        remoteWritten = vrb->syncFile->data->written;
    
        ++tries;
    }
}
