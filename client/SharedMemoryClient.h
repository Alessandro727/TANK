#ifndef sharedmemoryclient_h
#define sharedmemoryclient_h

#include "../buffers/VirtualSHMDoubleRingBuffer.h"
#include "../buffers/VirtualSHMRingBuffer.h"

#include <sys/socket.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

//#define BUFFER_SIZE 1048576
//#define BUFFER_SIZE 4096
//#define BUFFER_SIZE 8192
//#define BUFFER_SIZE 2097152
//#define BUFFER_SIZE 4194304
//#define BUFFER_SIZE 8388608
#define BUFFER_SIZE 16777216
//#define BUFFER_SIZE 33554432
//#define BUFFER_SIZE 67108864
//#define BUFFER_SIZE 536870912
//#define BUFFER_SIZE 4294967296
//#define BUFFER_SIZE 8589934592

typedef struct {

	int initialUnixSocket;
    SHMDoubleRingBuffer* messageBuffer;

} SharedMemoryClient;

typedef struct {

	int initialUnixSocket;
    SHMRingBuffer* commBuffer;

} SharedMemoryClientSingleBuffer;

SharedMemoryClient* createSharedMemoryClient();

SharedMemoryClientSingleBuffer* createSharedMemoryClientSingleBuffer();

void connectFromSHMClient(SharedMemoryClient*, char*);

void writeSHMClient(SharedMemoryClient*, void*, unsigned long long);

void readSHMClient(SharedMemoryClient*, void*, unsigned long long);

void writeSHMClientSingleBuffer(SharedMemoryClientSingleBuffer*, void*, unsigned long long);

void readSHMSClientSingleBuffer(SharedMemoryClientSingleBuffer*, void*, unsigned long long);

unsigned long long readSomeSHMClient(SharedMemoryClient*, uint8_t*, unsigned long long);

unsigned long long readNoBlockingSHMClient(SharedMemoryClient*, void*, unsigned long long);

#ifdef __cplusplus
}
#endif

#endif
