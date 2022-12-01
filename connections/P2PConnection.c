#include "P2PConnection.h"
#include "../utils/utils.h"

ConnectionClient* createClient(char* localIp, char* remoteIp, char* localPort, char* remotePort, ConnType type) {

	ConnectionClient* conn = (ConnectionClient*) malloc(sizeof(ConnectionClient));

	char** list = getLocalIpList();

	bool isLocal = isLocalAddress(remoteIp);

	if (type == SHM && !isLocal) {
		type = RDMA;
		printf("\n Warning: Unable to establish connection via Shared Memory with remote machines. Type changed to RDMA. \n");

	}

	if (type != RDMA && type != SHM) {
		if (isLocal) {
			type = SHM;
		} else {
			type = RDMA;
		}
	}

	conn->type = type;

	if (conn->type == SHM) {

		char unixfile[50] = "/tmp/shm_";
		strcat(unixfile, remotePort);
		strcat(unixfile, "_");
		strcat(unixfile, localPort);

		conn->ShmClient = createSharedMemoryClient();
		connectFromSHMClient(conn->ShmClient, unixfile);

	} else {

		conn->RdmaClient = createRDMAClient();
        connectFromRDMAClient(conn->RdmaClient, remoteIp, remotePort);
    }
	return conn;
}

ConnectionClient* createClientWithSocket(char* localIp, char* remoteIp, char* localPort, char* remotePort, int socket, ConnType type) {

	ConnectionClient* conn = (ConnectionClient*) malloc(sizeof(ConnectionClient));

	char** list = getLocalIpList();

	bool isLocal = isLocalAddress(remoteIp);

	if (type == SHM && !isLocal) {
		type = RDMA;
		printf("\n Warning: Unable to establish connection via Shared Memory with remote machines. Type changed to RDMA. \n");

	}

	if (type != RDMA && type != SHM) {
		if (isLocal) {
			type = SHM;
		} else {
			type = RDMA;
		}
	}

	conn->type = type;

	if (conn->type == SHM) {

		char unixfile[50] = "/tmp/shm_";
		strcat(unixfile, remotePort);
		strcat(unixfile, "_");
		strcat(unixfile, localPort);

		conn->ShmClient = createSharedMemoryClient();
        connectFromSHMClient(conn->ShmClient, unixfile);

	} else {


		conn->RdmaClient = createRDMAClientWithSocket(socket, localIp);
		connectFromRDMAClient(conn->RdmaClient, remoteIp, remotePort);

	}

	return conn;
}

ConnectionServer* createServer(char* localIp, char* remoteIp, char* localPort, char* remotePort, ConnType type) {

	ConnectionServer* conn = (ConnectionServer*) malloc(sizeof(ConnectionServer));

	bool isLocal = isLocalAddress(remoteIp);

    if (type == SHM && !isLocal) {
        type = RDMA;
        printf("\n Warning: Unable to establish connection via Shared Memory with remote machines. Type changed to RDMA. \n");
    }

    if (type != RDMA && type != SHM) {
    printf("Type is  NULL\n");
        if (isLocal) {
                type = SHM;
        } else {
                type = RDMA;
        }
    }

    conn->type = type;

    if (conn->type == SHM) {

        char unixfile[50] = "/tmp/shm_";

        strcat(unixfile, localPort);

        strcat(unixfile, "_");

        strcat(unixfile, remotePort);


        conn->ShmServer = createSharedMemoryServer(unixfile);
        acceptFromSHMServer(conn->ShmServer,unixfile);

	} else {

		conn->RdmaServer = createRDMAServer(remoteIp, localPort);
        acceptFromRDMAServer(conn->RdmaServer, localIp);
	}
	return conn;
}

ConnectionServer* createServerWithSocket(char* localIp, char* remoteIp, char* localPort, char* remotePort, int socket, ConnType type) {

	ConnectionServer* conn = (ConnectionServer*) malloc(sizeof(ConnectionServer));

	bool isLocal = isLocalAddress(remoteIp);


        if (type == SHM && !isLocal) {
                type = RDMA;
                printf("\n Warning: Unable to establish connection via Shared Memory with remote machines. Type changed to RDMA. \n");
        }

        if (type != RDMA && type != SHM) {
		printf("Type is  NULL\n");
                if (isLocal) {
                        type = SHM;
                } else {
                        type = RDMA;
                }
        }

        conn->type = type;

        if (conn->type == SHM) {

                char unixfile[50] = "/tmp/shm_";

                strcat(unixfile, localPort);

                strcat(unixfile, "_");

                strcat(unixfile, remotePort);


		conn->ShmServer = createSharedMemoryServer(unixfile);
		acceptFromSHMServer(conn->ShmServer,unixfile);

	} else {

		conn->RdmaServer = createRDMAServerWithSocket(socket, localIp);
        acceptFromRDMAServer(conn->RdmaServer, localIp);
	}
	return conn;
}

bool isLocalAddress(char* ip) {

	char** list = getLocalIpList();

	for (int c = 0; c < MAX_IP_ADDRESS_COUNT; c++) {
                if (strcmp(list[c], ip) == 0) {
                	return true;
                }
        }
	return false;
}

void ClientRead(ConnectionClient* client, void* buffer, unsigned long long size) {

    if (client->type == RDMA) {
        readRDMAClient(client->RdmaClient, buffer, size);
    } else {
        readSHMClient(client->ShmClient, buffer, size);
    }
}

void ClientWrite(ConnectionClient* client, void* buffer, unsigned long long size) {

    if (client->type == RDMA) {
        writeRDMAClient(client->RdmaClient, buffer, size);
    } else {
        writeSHMClient(client->ShmClient, buffer, size);
    }
}

unsigned long long ClientReadSome(ConnectionClient* client, void* buffer, unsigned long long maxSize) {

    if (client->type == RDMA) {
            readSomeRDMAClient(client->RdmaClient, buffer, maxSize);
    } else {
            readSomeSHMClient(client->ShmClient, buffer, maxSize);
    }
}

void ServerRead(ConnectionServer* server, void* buffer, unsigned long long size) {

	if (server->type == RDMA) {
        readRDMAServer(server->RdmaServer, buffer, size);
	} else {
		readSHMServer(server->ShmServer, buffer, size);
	}
}

void ServerWrite(ConnectionServer* server, void* buffer, unsigned long long size) {

    if (server->type == RDMA) {
        writeRDMAServer(server->RdmaServer, buffer, size);
    } else {
        writeSHMServer(server->ShmServer, buffer, size);
    }
}

unsigned long long ServerReadSome(ConnectionServer* server, void* buffer, unsigned long long maxSize) {

    if (server->type == RDMA) {
        readSomeRDMAServer(server->RdmaServer, buffer, maxSize);
    } else {
        readSomeSHMServer(server->ShmServer, buffer, maxSize);
    }
}
