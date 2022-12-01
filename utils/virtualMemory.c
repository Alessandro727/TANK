#include "virtualMemory.h"


CircularBuffer* createCircularBuffer(int fd, uint8_t* data) {

	CircularBuffer* circularbuffer = (CircularBuffer*) malloc(sizeof(CircularBuffer));

    circularbuffer->fd = fd;

    circularbuffer->data = data;

	return circularbuffer;
}

void destroyCircularBuffer(CircularBuffer* cb) {
    free(cb);
}

SyncFile* createSyncFile(int fd, CircularBufferInfo* data)	{

	SyncFile* syncfile = (SyncFile*) malloc(sizeof(SyncFile));

	syncfile->fd = fd;
	
    data->read = 0;
	
    data->written = 0;
	
    syncfile->data = data;

	return syncfile;
}

void destroySyncFile(SyncFile* sf) {
    free(sf);
}

SyncFile* mmapLocalSyncFile(char* name, size_t size, void *addr) {

	// create a new mapping in /dev/shm
    int fd = memfd_create(name, MFD_CLOEXEC);
    if (fd < 0) {
        perror("memfd_create");
        perror("memfd_create failed");
        exit(EXIT_FAILURE);

    }
    if (ftruncate(fd, size) != 0) {
        perror("ftruncate");
        perror("ftruncate failed");
        exit(EXIT_FAILURE);
    }

    void* ptr = mmap(addr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    memset(ptr, 0, size);

    return createSyncFile(fd, (CircularBufferInfo*)(ptr));

}

SyncFile* mmapRemoteSyncFile(int fd, size_t size, void *addr) {

    void* ptr = mmap(addr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    return createSyncFile(fd, (CircularBufferInfo *)(ptr) );
}


CircularBuffer* mmapRemoteCircularBuffer(int fd, unsigned long long size, bool init) {

    if (ftruncate(fd, size) != 0) {
        perror("ftruncate");
        perror("ftruncate failed");
        exit(EXIT_FAILURE);
    }

    //char* ptr = mmapBuffer(fd, size);
    uint8_t* ptr = mmapBuffer(fd, size);

    // because of the overlap, we need no deleter and unmapping for those mappings
    if (init)   {
        memset(ptr, 0, size);
    } 

    return createCircularBuffer(fd, ptr);

}


CircularBuffer* mmapLocalCircularBuffer(char* name, unsigned long long size) {

    char *e;
    int pos;

    e = strchr(name, '/');
    pos = (int)(e - name);

    if (pos == -1) {
        pos = 0;
    }

    int fd = memfd_create(name + pos, MFD_CLOEXEC);
    if (fd < 0) {
        perror("memfd_create");
        perror("memfd_create failed");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd, size) != 0) {
        perror("ftruncate");
        perror("ftruncate failed");
        exit(EXIT_FAILURE);
    }

    //char* ptr = mmapBuffer(fd, size);
    uint8_t* ptr = mmapBuffer(fd, size);

    memset(ptr, 0, size);

    return createCircularBuffer(fd, ptr);
	
}


uint8_t* mmapBuffer(int fd, unsigned long long size) {

    // first acquire enough continuous memory
    //char* ptr = (char *)(
    uint8_t* ptr = (uint8_t*)(
            mmap(NULL, size * 2, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)
    );

    // map the shared memory to the first half
    if (mmap(ptr, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0) != ptr) {
        perror("mmaping the first circular buffer failed ");
        printf( "Value of errno: %d\n", errno );
        exit(EXIT_FAILURE);
    }

    // and also to the second half
    if (mmap(&ptr[size], size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0) != &ptr[size]) {
        perror("mmaping the second circular buffer failed ");
        printf( "Value of errno: %d\n", errno );
        exit(EXIT_FAILURE);
    }
    return (uint8_t*) ptr;
}


