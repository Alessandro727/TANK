#include "TcpServer.h"

TcpServer* createTcpServer(const char* port) {

    TcpServer* tcpServer = malloc(sizeof(TcpServer));

    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(port));

	int opt = 1;

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
	{
     		perror("setsockopt");
        	exit(EXIT_FAILURE);
	}

    tcpServer->initialSocket_desc = sockfd;

    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    return tcpServer;

}


void writeTCPServer(TcpServer* tcpServer, uint16_t* buffer, size_t size) {

    int communciationSocket = tcpServer->communicationSocket_desc;

    for (size_t current = 0; size > 0;) {
      int res = send(communciationSocket, (const char*) buffer + current, size, 0);

      if (res < 0) {
         printf("Couldn't write to socket server: %s", strerror(errno));
         exit(EXIT_FAILURE);
      }

      current += res;

      size -= res;
    }

}

void readTCPServer(TcpServer* tcpServer, uint16_t* buffer, size_t size) {


    int communicationSocket = tcpServer->communicationSocket_desc;

    for (size_t current = 0; size > 0;) {

        size_t res = recv(communicationSocket, (char*) buffer + current, size, 0);

        if (res < 0) {
            printf("Couldn't read to socket server: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if ((size_t) res == size) {
            return res;
        }
        current += res;

        size -= res;
    }

}

size_t readSomeTCPServer(TcpServer* tcpServer, uint8_t *buffer, size_t maxSize) {

    int communicationSocket = tcpServer->communicationSocket_desc;

    int res = read(communicationSocket, &buffer[0], maxSize);

    if (res < 0) {
         printf("Couldn't read to socket: %s", strerror(errno));
    }
      
    return res;
}

void acceptFromTCPServer(TcpServer* tcpServer) {

    int new_socket = acceptTCPLoop(tcpServer->initialSocket_desc);

    tcpServer->communicationSocket_desc = new_socket;
}


int acceptTCPLoop(int sock_desc) {

    int nsock;

    while ( true ) {
        nsock = accept4(sock_desc, NULL, NULL, SOCK_NONBLOCK);
        //acced = accept(sock_desc, NULL, NULL);

        if ( nsock >= 0 ) {
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

    return nsock;
}

