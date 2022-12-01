#include "VirtualSHMDoubleRingBuffer.h"

SHMDoubleRingBuffer* createSHMDoubleRingBuffer(unsigned long long size, int communicationSocket, char* filename)    {

    SHMDoubleRingBuffer* ringbuffer = (SHMDoubleRingBuffer*) malloc(sizeof(SHMDoubleRingBuffer));

    ringbuffer->bufferName = "/sharedBuffer";

    ringbuffer->syncFileName = "/sharedSyncFile";

    ringbuffer->size = size;

    ringbuffer->bitmask = size - 1;

    ringbuffer->shmFileName = filename;

    ringbuffer->cachedRemoteRead = 0;

    bool powerOfTwo = (size != 0) && !(size & (size - 1));

    if (!powerOfTwo) {
        perror("size should be a power of 2");
	    exit(EXIT_FAILURE);
    }

    uuid_t binuuid;

    uuid_generate_random(binuuid);

    char randomUUID[37];

    uuid_unparse_lower(binuuid, randomUUID);

    ringbuffer->localSyncFile = createAndSendLocalSyncFile(communicationSocket, ringbuffer->syncFileName, randomUUID);

    ringbuffer->localCircularBuffer = createAndSendLocalCircularBuffer(communicationSocket, ringbuffer->bufferName, randomUUID, size);

    int remoteSyncFileFd = receive_fd(communicationSocket);

    ringbuffer->remoteSyncFile = mmapRemoteSyncFile(remoteSyncFileFd, sizeof(CircularBufferInfo), NULL);

    int remoteFd = receive_fd(communicationSocket);

    ringbuffer->remoteCircularBuffer = mmapRemoteCircularBuffer(remoteFd, size, false);

    return ringbuffer;
}

SHMDoubleRingBuffer* createSHMDoubleRingBufferFromSingleBuffer(unsigned long long size, int communicationSocket, char* filename, SHMRingBuffer* comBuff)    {

    SHMDoubleRingBuffer* ringbuffer = (SHMDoubleRingBuffer*) malloc(sizeof(SHMDoubleRingBuffer));

    ringbuffer->bufferName = "/sharedBuffer";

    ringbuffer->syncFileName = "/sharedSyncFile";

    ringbuffer->size = size; 

    ringbuffer->bitmask = size - 1;

    ringbuffer->shmFileName = filename;

    ringbuffer->cachedRemoteRead = 0;

    bool powerOfTwo = (size != 0) && !(size & (size - 1));

    if (!powerOfTwo) {
        perror("size should be a power of 2");
        exit(EXIT_FAILURE);
    }

    uuid_t binuuid;

    uuid_generate_random(binuuid);

    char randomUUID[37];

    uuid_unparse_lower(binuuid, randomUUID);

    ringbuffer->localSyncFile = comBuff->syncFile;

    send_fd(communicationSocket, comBuff->syncFile->fd);

    ringbuffer->localCircularBuffer = comBuff->circularBuffer;

    send_fd(communicationSocket, comBuff->circularBuffer->fd);

    int remoteSyncFileFd = receive_fd(communicationSocket);

    ringbuffer->remoteSyncFile = mmapRemoteSyncFile(remoteSyncFileFd, sizeof(CircularBufferInfo), NULL);

    int remoteFd = receive_fd(communicationSocket);

    ringbuffer->remoteCircularBuffer = mmapRemoteCircularBuffer(remoteFd, size, false);

    return ringbuffer;
}

SyncFile* createAndSendLocalSyncFile(int communicationSocket, char* syncFileName, char* uuid) {

    char* new_syncFileName = (char*) malloc(strlen(syncFileName)+1+37);

    strcpy(new_syncFileName, syncFileName);
    
    strcat(new_syncFileName, uuid);

    SyncFile* syncFile = mmapLocalSyncFile(new_syncFileName, sizeof(CircularBufferInfo), NULL);

    send_fd(communicationSocket, syncFile->fd);

    return syncFile;
}

CircularBuffer* createAndSendLocalCircularBuffer(int communicationSocket, char* bufferName, char* uuid, unsigned long long size) {

    char* new_bufferName = (char*) malloc(strlen(bufferName)+1+37);

    strcpy(new_bufferName, bufferName);

    strcat(new_bufferName, uuid);

    CircularBuffer* circularBuffer = mmapLocalCircularBuffer(new_bufferName, size);

    send_fd(communicationSocket, circularBuffer->fd);

    return circularBuffer;
}

unsigned long long writeSHMDoubleRingBuffer(SHMDoubleRingBuffer* vrb, void *data, unsigned long long length) {

    atomic_ullong localWritten = atomic_load(&(vrb->localSyncFile->data->written));

    unsigned long long pos = localWritten & vrb->bitmask;

    blockUntilLocalBufferFree(vrb, localWritten, length);

    //memmove(&vrb->localCircularBuffer->data[pos], data, length);
    memcpy(&vrb->localCircularBuffer->data[pos], data, length);

    atomic_store(&(vrb->localSyncFile->data->written), localWritten + length);

    return length;
}

unsigned long long receiveSHMDoubleRingBuffer(SHMDoubleRingBuffer* vrb, void *whereTo, unsigned long long maxSize) {

    atomic_ullong localRead = atomic_load(&(vrb->localSyncFile->data->read));

    unsigned long long pos = localRead & vrb->bitmask;

    blockUntilRemoteBufferAvailable(vrb, maxSize, localRead);

    memcpy((int*)(whereTo), &vrb->remoteCircularBuffer->data[pos], maxSize);
    //memmove((int*)(whereTo), &vrb->remoteCircularBuffer->data[pos], maxSize);

    atomic_store(&(vrb->localSyncFile->data->read), localRead + maxSize);

    return maxSize;
}

unsigned long long receiveNoBlockingSHMDoubleRingBuffer(SHMDoubleRingBuffer* vrb, void *whereTo, unsigned long long maxSize) {

    atomic_ullong localRead = atomic_load(&(vrb->localSyncFile->data->read));

    atomic_ullong remoteWritten = atomic_load(&(vrb->remoteSyncFile->data->written));

    unsigned long long pos = localRead & vrb->bitmask;

    unsigned long long readSize = mymin(remoteWritten - localRead, maxSize);

    memcpy((int*)(whereTo), &vrb->remoteCircularBuffer->data[pos], readSize);
    //memmove((int*)(whereTo), &vrb->remoteCircularBuffer->data[pos], readSize);

    atomic_store(&(vrb->localSyncFile->data->read), localRead + readSize);

    return readSize;
}

unsigned long long receiveSomeSHMDoubleRingBuffer(SHMDoubleRingBuffer* vrb, void *whereTo, unsigned long long maxSize) {

    atomic_ullong localRead = atomic_load(&(vrb->localSyncFile->data->read));

    unsigned long long pos = localRead & vrb->bitmask;

    blockUntilRemoteBufferAvailable(vrb, 1, localRead);

    atomic_ullong written = atomic_load(&(vrb->remoteSyncFile->data->written));
    unsigned long long size = mymin(written - localRead, maxSize);

    memcpy((uint8_t *)(whereTo), &vrb->remoteCircularBuffer->data[pos], size);

    atomic_store(&(vrb->localSyncFile->data->read), localRead + size);
    return size;
}

void blockUntilLocalBufferFree(SHMDoubleRingBuffer* vrb, atomic_ullong localWritten, unsigned long long length) {

    if ((localWritten - vrb->cachedRemoteRead) <= (vrb->size - length)) {
        	return;
	}

    int tries = 0;

    while ((localWritten - vrb->cachedRemoteRead) > (vrb->size - length))   {

        yield(tries);

        vrb->cachedRemoteRead = vrb->remoteSyncFile->data->read;

        ++tries;
    }
}

void blockUntilRemoteBufferAvailable(SHMDoubleRingBuffer* vrb, unsigned long long maxSize, atomic_ullong localRead) {

    unsigned long long remoteWritten = vrb->remoteSyncFile->data->written;

    int tries = 0;

    while ((remoteWritten - localRead) < maxSize) {

        yield(tries);

        remoteWritten = vrb->remoteSyncFile->data->written;

        ++tries;
    }
}
