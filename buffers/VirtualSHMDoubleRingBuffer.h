#ifndef virtualshmdoubleringbuffer_h
#define virtualshmdoubleringbuffer_h

#include "../utils/virtualMemory.h"
#include "../utils/utils.h"
#include "VirtualSHMRingBuffer.h"

#include <stdlib.h>
#include <stdint.h>
#include <sys/socket.h>
#include <errno.h>
#include <uuid/uuid.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <xmmintrin.h>
#include <stdbool.h>
#include <math.h>
#include <immintrin.h>
#include <assert.h>
#include <inttypes.h>

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif


typedef struct {
	char* bufferName;
    char* syncFileName;
    unsigned long long size;
    unsigned long long bitmask;
    char* shmFileName;

    SyncFile* localSyncFile;
    CircularBuffer* localCircularBuffer;

    unsigned long long cachedRemoteRead;

    SyncFile* remoteSyncFile;
    CircularBuffer* remoteCircularBuffer;

} SHMDoubleRingBuffer;


SHMDoubleRingBuffer* createSHMDoubleRingBuffer(unsigned long long, int, char*);

SHMDoubleRingBuffer* createSHMDoubleRingBufferFromSingleBuffer(unsigned long long, int, char*, SHMRingBuffer*);

unsigned long long writeSHMDoubleRingBuffer(SHMDoubleRingBuffer*, void*, unsigned long long);

unsigned long long receiveSHMDoubleRingBuffer(SHMDoubleRingBuffer*, void*, unsigned long long);

unsigned long long receiveSomeSHMDoubleRingBuffer(SHMDoubleRingBuffer*, void*, unsigned long long);

void blockUntilLocalBufferFree(SHMDoubleRingBuffer*, atomic_ullong, unsigned long long);

void blockUntilRemoteBufferAvailable(SHMDoubleRingBuffer*, unsigned long long, atomic_ullong);

SyncFile* createAndSendLocalSyncFile(int, char*, char*);

CircularBuffer* createAndSendLocalCircularBuffer(int, char*, char*, unsigned long long);

unsigned long long receiveNoBlockingSHMDoubleRingBuffer(SHMDoubleRingBuffer*, void*, unsigned long long);

#ifdef __cplusplus
}
#endif

#endif
