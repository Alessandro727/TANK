#ifndef network_h
#define network_h

#include <stdio.h>
#include <infiniband/verbs.h>
#include "CompletionQueuePair.h"
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ifaddrs.h>



#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

#define RED "\e[0;31m"
#define NC "\e[0m"

typedef struct {

    struct QueuePair* queuePair;
    uint32_t maxWr;
    // static constexpr uint32_t maxWr = 2;
    uint32_t maxSge;

    // The port of the Infiniband device
    uint8_t ibport;

    // The Infiniband devices
    struct ibv_device **device_list;
    // The verbs context
    struct ibv_context* context;
    // The global protection domain
    struct ibv_pd* protectionDomain;

    // Shared Queues
    CompletionQueuePair sharedCompletionQueuePair;

    struct ibv_srq* sharedReceiveQueue;

} Network;

typedef struct {

    union ibv_gid gid;
    uint32_t qpn;
    uint16_t lid;

} Address;


Network* createNetwork(char*);

char* getNameFromIP(char*);

// Get the LID
uint16_t getLID(Network*);

// Get the GID
union ibv_gid getGID(Network*);

CompletionQueuePair* getSharedCompletionQueue(Network*);

CompletionQueuePair newCompletionQueuePair(Network*);

struct ibv_pd* getProtectionDomain(Network*);

/// Register a new MemoryRegion
struct ibv_mr* registerMr(Network, void*, size_t, enum ibv_access_flags);

#ifdef __cplusplus
}
#endif

#endif