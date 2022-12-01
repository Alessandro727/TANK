#include "SharedMemoryClient.h"

#define mymin(a,b) fmin(a,b)
#define SA struct sockaddr

SharedMemoryClient* createSharedMemoryClient() {

    SharedMemoryClient* shmtc = (SharedMemoryClient*) malloc(sizeof(SharedMemoryClient));

	int sock_fd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0);
	shmtc->initialUnixSocket = sock_fd;

	return shmtc;
}

SharedMemoryClientSingleBuffer* createSharedMemoryClientSingleBuffer() {

    SharedMemoryClientSingleBuffer* shmstc = (SharedMemoryClientSingleBuffer*) malloc(sizeof(SharedMemoryClientSingleBuffer));

    int sock_fd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0);
    shmstc->initialUnixSocket = sock_fd;

    return shmstc;
}


void connectFromSHMClient(SharedMemoryClient* shmTC, char* file) {

    int initialUnixSocket = shmTC->initialUnixSocket;

    struct sockaddr_un name;

    memset(&name, 0, sizeof(name));

    name.sun_family = AF_UNIX;
    
    strncpy(name.sun_path, file, sizeof(name.sun_path) - 1);

    for (int i = 0;; ++i) {

	    int v = connect(initialUnixSocket, (struct sockaddr *)(&name), sizeof name);
        if (v == 0) {
		    if (unlink(file) < 0) {
                	perror("error unlink'ing");
                    printf( "Value of errno: %d\n", errno );
            }
        	break;
        }
    }

    shmTC->messageBuffer = createSHMDoubleRingBuffer(BUFFER_SIZE, initialUnixSocket, file);
}

void writeSHMClient(SharedMemoryClient* shmTC, void* data, unsigned long long size)	{

	for (unsigned long long i = 0; i < size;) {

        unsigned long long chunk = mymin(size - i, BUFFER_SIZE);

        writeSHMDoubleRingBuffer(shmTC->messageBuffer, data + i, chunk);
        
        i += chunk;
	}
}

void readSHMClient(SharedMemoryClient* shmTC, void* buffer, unsigned long long size) {

	for (unsigned long long i = 0; i < size;) {

        unsigned long long chunk = mymin(size - i, BUFFER_SIZE);
        
        receiveSHMDoubleRingBuffer(shmTC->messageBuffer, buffer + i, chunk);
        
        i += chunk;
	}
}

unsigned long long readNoBlockingSHMClient(SharedMemoryClient* shmTC, void* buffer, unsigned long long maxSize) {

        unsigned long long size = receiveNoBlockingSHMDoubleRingBuffer(shmTC->messageBuffer, buffer, maxSize);
        
        return size;
}

void writeSHMClientSingleBuffer(SharedMemoryClientSingleBuffer* shmSTC, void* data, unsigned long long size) {

    for (unsigned long long i = 0; i < size;) {

        unsigned long long chunk = mymin(size - i, BUFFER_SIZE);    

        writeSHMRingBuffer(shmSTC->commBuffer, data + i, chunk);
        
        i += chunk;
   }
}

void readSHMClientSingleBuffer(SharedMemoryClientSingleBuffer* shmSTC, void* buffer, unsigned long long size) {

    for (unsigned long long i = 0; i < size;) {
        unsigned long long chunk = mymin(size - i, BUFFER_SIZE);
        
        receiveSHMRingBuffer(shmSTC->commBuffer, buffer + i, chunk);
        
        i += chunk;
    }
}

unsigned long long readSomeSHMClient(SharedMemoryClient* shmTC, uint8_t* buffer, unsigned long long size) {

	unsigned long long chunk = mymin(size, BUFFER_SIZE);

	return receiveSomeSHMDoubleRingBuffer(shmTC->messageBuffer, buffer, chunk);

}