#include "Network.h"

Network* createNetwork(char* ip) {

    Network* network = (Network*) malloc(sizeof(Network));

//  network->maxWr  = 16351;
	network->maxWr  = 32767;
    network->maxSge = 30;
    network->ibport = 1;

    int num_devices;

    network->device_list = ibv_get_device_list(&num_devices);
    if (!network->device_list) {

        printf("Error, ibv_get_device_list() failed\n");
        exit(EXIT_FAILURE);
    }

    char* interfaceName = getNameFromIP(ip);

    char command[50] = {'\0'};

    strcat(command,"ibdev2netdev | egrep ");

    strcat(command, interfaceName);

    strcat(command," | awk '{print $1;}'");

    FILE *fp;
    char path[20];

    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
    }
    /* Read the output a line at a time - output it. */
    fgets(path, sizeof(path), fp);
    /* close */
    pclose(fp);

    network->context = ibv_open_device(network->device_list[0]);

    for (int i = 0; i < num_devices; i++) {
        if (!strcmp(path,network->device_list[i]->name)) {
            network->context = ibv_open_device(network->device_list[i]);
            break;
        }
    }

    if (!network->context) {

        printf("Error, failed to open the device '%s'\n",
                ibv_get_device_name(network->device_list[0]));
        exit(EXIT_FAILURE);
    }

    network->protectionDomain = ibv_alloc_pd(network->context);


    network->sharedCompletionQueuePair = createCompletionQueuePair(network->context);

    struct ibv_srq_init_attr srq_init_attr;

    memset(&srq_init_attr, 0, sizeof(srq_init_attr));

    srq_init_attr.attr.max_wr  = network->maxWr;
    srq_init_attr.attr.max_sge = network->maxSge;

    network->sharedReceiveQueue = ibv_create_srq(network->protectionDomain, &srq_init_attr);

    return network;
}

char* getNameFromIP(char* localIP) {

    struct ifaddrs *addresses;
    if (getifaddrs(&addresses) == -1) {
        printf("getifaddrs call failed\n");
        return "NoName";
    }

    struct ifaddrs *address = addresses;
    while(address) {
        int family = address->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {
            char ap[100];
            const int family_size = family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
            getnameinfo(address->ifa_addr,family_size, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
            if (!strcmp(localIP, ap)) {
                return address->ifa_name;
            }
        }
        address = address->ifa_next;
    }
    freeifaddrs(addresses);
    return "NoName";
}


// Get the LID
uint16_t getLID(Network* net) {

    struct ibv_port_attr port_attr;

    int rc = ibv_query_port(net->context, net->ibport, &port_attr);

    return port_attr.lid;

}

// Get the GID
union ibv_gid getGID(Network* net) {

    union ibv_gid gid;

    int rc = ibv_query_gid(net->context, net->ibport, 0, &gid);

    return gid;

}


CompletionQueuePair* getSharedCompletionQueue(Network* net) {
    return &(net->sharedCompletionQueuePair);
}

struct ibv_pd* getProtectionDomain(Network* net) {
    return net->protectionDomain;
}

/// Register a new MemoryRegion
struct ibv_mr* registerMr(Network net, void *addr, size_t length, enum ibv_access_flags access) {

	struct ibv_mr* mr = ibv_reg_mr(net.protectionDomain, addr, length, access);
    if (!mr) {
		printf("Error, ibv_reg_mr() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return mr;
}

CompletionQueuePair newCompletionQueuePair(Network* net) {
    return createCompletionQueuePair(net->context);
}
