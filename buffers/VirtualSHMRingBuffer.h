#ifndef virtualshmringbuffer_h
#define virtualshmringbuffer_h

#include "../utils/virtualMemory.h"
#include "../utils/utils.h"
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
#include <atomic>
using namespace std;
#else
#include <stdatomic.h>
#endif

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif



typedef struct {

	char* bufferName;
    char* syncFileName;
    unsigned long long size;
    unsigned long long bitmask;
    char* name;

    SyncFile* syncFile;
    CircularBuffer* circularBuffer;

} SHMRingBuffer;


SHMRingBuffer* createSHMRingBuffer(unsigned long long, char*);

void shareSHMRingBuffer(int, SHMRingBuffer*);

SHMRingBuffer* acquireSHMRingBufferr(int, unsigned long long, char*);

unsigned long long writeSHMRingBuffer(SHMRingBuffer*, void*, unsigned long long);

unsigned long long receiveSHMRingBuffer(SHMRingBuffer*, void*, unsigned long long);

void blockUntilBufferFree(SHMRingBuffer*, atomic_ullong, unsigned long long);

void blockUntilBufferAvailable(SHMRingBuffer*, unsigned long long, atomic_ullong);

#ifdef __cplusplus
}
#endif

#endif
