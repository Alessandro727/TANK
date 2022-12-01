#ifndef sharedmemoryserver_h
#define sharedmemoryserver_h



#include "../buffers/VirtualSHMDoubleRingBuffer.h"
#include "../buffers/VirtualSHMRingBuffer.h"

#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

//x#define BUFFER_SIZE 1048576

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
	char* socket_file;
	int communicationUnixSocket;
    SHMDoubleRingBuffer* messageBuffer;

} SharedMemoryServer;

typedef struct {

	int initialUnixSocket;
	char* socket_file;
	int communicationUnixSocket;
	SHMRingBuffer * commBuffer;

} SharedMemoryServerSingleBuffer;


SharedMemoryServer* createSharedMemoryServer(char*);

SharedMemoryServerSingleBuffer* createSharedMemoryServerSingleBuffer(char*);

int openUnixSocket(char*);

int acceptSHMLoop(int);

void acceptFromSHMServer(SharedMemoryServer*, char*);

void writeSHMServer(SharedMemoryServer*, void*, unsigned long long);

void writeSHMServerSingleBuffer(SharedMemoryServerSingleBuffer*, void*, unsigned long long);

void readSHMServer(SharedMemoryServer*, void*, unsigned long long);

void readSHMServerSingleBuffer(SharedMemoryServerSingleBuffer*, void*, unsigned long long);

unsigned long long readSomeSHMServer(SharedMemoryServer*, uint8_t*, unsigned long long);

void bindSHM(int,  char*);

void listenSHM(int);

unsigned long long readNoBlockingSHMServer(SharedMemoryServer*, void*, unsigned long long);

#ifdef __cplusplus
}
#endif

#endif
