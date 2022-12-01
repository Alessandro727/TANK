#ifndef p2pconnection_h
#define p2pconnection_h

#include "../client/SharedMemoryClient.h"
#include "../server/SharedMemoryServer.h"
#include "../client/RdmaClient.h"
#include "../server/RdmaServer.h"
#include "../utils/utils.h"

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

typedef enum {
	RDMA,
	SHM
} ConnType;

typedef struct {

	SharedMemoryClient* ShmClient;
	RdmaClient* RdmaClient;
	ConnType type;

} ConnectionClient;

typedef struct {

    SharedMemoryServer* ShmServer;
    RdmaServer* RdmaServer;
	ConnType type;

} ConnectionServer;


ConnectionClient* createClient(char*, char*, char*, char*, ConnType);

ConnectionClient* createClientWithSocket(char*, char*, char*, char*, int, ConnType);

ConnectionServer* createServer(char*, char*, char*, char*, ConnType);

ConnectionServer* createServerWithSocket(char*, char*, char*, char*, int, ConnType);

bool isLocalAddress(char*);

void ClientRead(ConnectionClient*, void*, unsigned long long);

void ClientWrite(ConnectionClient*, void*, unsigned long long);

unsigned long long ClientReadSome(ConnectionClient*, void*, unsigned long long);

void ServerRead(ConnectionServer*, void*, unsigned long long);

void ServerWrite(ConnectionServer*, void*, unsigned long long);

unsigned long long ServerReadSome(ConnectionServer*, void*, unsigned long long);

#ifdef __cplusplus
}
#endif

#endif
