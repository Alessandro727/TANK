//
// Created by Alessandro Fogli on 07/11/22.
//
#ifndef TANK_FILE_H
#define TANK_FILE_H


#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <sched.h>
#include <xmmintrin.h>
#include <sys/socket.h>
#include <immintrin.h>
#include <assert.h>
#include <inttypes.h>
#define _GNU_SOURCE
#include <sys/mman.h>



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


#define mymin(a,b) fmin(a,b)


typedef struct  {
    atomic_ullong read;
    atomic_ullong written;

} CircularBufferInfo;

typedef struct {
    int fd;
    uint8_t* data;

} CircularBuffer;

typedef struct {
    int fd;
    CircularBufferInfo* data;

} SyncFile;

CircularBuffer* createCircularBuffer(int, uint8_t*);

void destroyCircularBuffer(CircularBuffer* wb);

SyncFile* createSyncFile(int, CircularBufferInfo*);

void destroySyncFile(SyncFile* sm);

SyncFile* mmapLocalSyncFile(char*, size_t, void*);

SyncFile* mmapRemoteSyncFile(int, size_t, void*);

CircularBuffer* mmapRemoteCircularBuffer(int, unsigned long long, bool);

CircularBuffer* mmapLocalCircularBuffer(char*, unsigned long long);

uint8_t* mmapBuffer(int, unsigned long long);

#ifdef __cplusplus
}
#endif

#endif //TANK_FILE_H
