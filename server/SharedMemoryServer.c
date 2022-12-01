#include "SharedMemoryServer.h"

#define mymin(a,b) fmin(a,b)

SharedMemoryServer* createSharedMemoryServer(char* domainSocket)	{

    SharedMemoryServer* shms = (SharedMemoryServer*) malloc(sizeof(SharedMemoryServer));

    shms->socket_file = domainSocket;

    shms->initialUnixSocket = openUnixSocket(domainSocket);
	
    return shms;
}

SharedMemoryServerSingleBuffer* createSharedMemoryServerSingleBuffer(char* domainSocket)  {

    SharedMemoryServerSingleBuffer* shmssb = (SharedMemoryServerSingleBuffer*) malloc(sizeof(SharedMemoryServerSingleBuffer));

    shmssb->socket_file = domainSocket;

    shmssb->initialUnixSocket = openUnixSocket(domainSocket);
    
    return shmssb;
}

int openUnixSocket(char* domainSocket) {

    int socket_fd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0);
    
    bindSHM(socket_fd, domainSocket);
    
    listenSHM(socket_fd);

    return socket_fd;
}

void acceptFromSHMServer(SharedMemoryServer* shmTS, char* file) {

    int com_socket = acceptSHMLoop(shmTS->initialUnixSocket);

    shmTS->communicationUnixSocket = com_socket;

	shmTS->messageBuffer = createSHMDoubleRingBuffer(BUFFER_SIZE, shmTS->communicationUnixSocket, file);
}


void writeSHMServer(SharedMemoryServer* shmTS, void* data, unsigned long long size)	{

	for (unsigned long long i = 0; i < size;) {

        unsigned long long chunk = mymin(size - i, BUFFER_SIZE);

        writeSHMDoubleRingBuffer(shmTS->messageBuffer, data + i, chunk);
        
        i += chunk;
    }
}

void writeSHMServerSingleBuffer(SharedMemoryServerSingleBuffer* shmSTS, void* data, unsigned long long size) {

    for (unsigned long long i = 0; i < size;) {

        unsigned long long chunk = mymin(size - i, BUFFER_SIZE);    

        writeSHMRingBuffer(shmSTS->commBuffer, data + i, chunk);
        
        i += chunk;
    }
}


void readSHMServer(SharedMemoryServer* shmTS, void* buffer, unsigned long long size) {

	for (unsigned long long i = 0; i < size;) {
    
        unsigned long long chunk = mymin(size - i, BUFFER_SIZE);
        
        receiveSHMDoubleRingBuffer(shmTS->messageBuffer, buffer + i, chunk);
        
        i += chunk;
    }
}

void readSHMServerSingleBuffer(SharedMemoryServerSingleBuffer* shmSTS, void* buffer, unsigned long long size) {

	for (unsigned long long i = 0; i < size;) {
    
        unsigned long long chunk = mymin(size - i, BUFFER_SIZE);
        
        receiveSHMRingBuffer(shmSTS->commBuffer, buffer + i, chunk);

        i += chunk;
    }
}

unsigned long long readSomeSHMServer(SharedMemoryServer* shmTS, uint8_t* buffer, unsigned long long size) {

	unsigned long long chunk = mymin(size, BUFFER_SIZE);

	return receiveSomeSHMDoubleRingBuffer(shmTS->messageBuffer, buffer, chunk);
}

unsigned long long readSHMTS_v(SharedMemoryServer* shmTS, void* buffer, unsigned long long maxSize) {

    unsigned long long size = receiveNoBlockingSHMDoubleRingBuffer(shmTS->messageBuffer, buffer, maxSize);

    return size;
}

void bindSHM(int sock_desc,  char* pathToFile) {
   
    struct sockaddr_un my_addr;

   	memset(&my_addr, 0, sizeof(my_addr));
    
    my_addr.sun_family = AF_UNIX;
    
    strncpy(my_addr.sun_path, pathToFile, sizeof(my_addr.sun_path) - 1);
   
   	if (bind(sock_desc, (struct sockaddr *) &my_addr, sizeof(my_addr)) < 0) {
    
     	perror("error bind'ing");
     	printf( "Value of errno: %d\n", errno );
    	exit(EXIT_FAILURE);
   	}
}

void listenSHM(int sock_desc) {

	if (listen(sock_desc, SOMAXCONN) < 0) {

	    	perror("error close'ing");
    		printf( "Value of errno: %d\n", errno );
    		exit(EXIT_FAILURE);
  	}
}

int acceptSHMLoop(int socket) {

    int com_socket;
    while ( true ) {
    
        com_socket = accept4(socket, NULL, NULL, SOCK_NONBLOCK);
    
        if ( com_socket >= 0 ) {
            break;
        }

        if ( errno == EAGAIN || errno == EINTR || errno == ECONNABORTED) {
            continue;
        } else {
            perror("error accept'ing");
            printf( "Value of errno: %d\n", errno );
            exit(EXIT_FAILURE);
        }
    }

    return com_socket;
}








