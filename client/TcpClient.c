#include "TcpClient.h"

TcpClient* createTcpClient() {

    TcpClient* tcpClient = malloc(sizeof(TcpClient));

    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    tcpClient->socket = socket_desc;
    int opt = 1;

    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    return tcpClient;
}


int connectFromTCPClient(TcpClient* tcpClient, char* ip, char* port) {

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));

    if(inet_pton(AF_INET, ip, &addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    int v = connect(tcpClient->socket, (struct sockaddr *)&addr, sizeof(addr));

    return v;
}

void writeTCPClient(TcpClient* tcpClient, char* buffer, size_t size) {

     int communicationSocket = tcpClient->socket;
     for (size_t current = 0; size > 0;) {
	      int res = send(communicationSocket, (char*) buffer + current, size, 0);
	      if (res < 0) {
	         printf("Couldn't write to socket client: %s", strerror(errno));
	         exit(EXIT_FAILURE);
	      }
	      current += res;
	      size -= res;
     }
}


void readTCPClient(TcpClient* tcpClient, char* buffer, size_t size) {

	int communicationSocket = tcpClient->socket;

	for (size_t current = 0; size > 0;) {
    		size_t res = recv(communicationSocket, (char*) buffer + current, size, 0);
        	if (res < 0) {
	        	printf("Couldn't read to socket client: %s", strerror(errno));
		        exit(EXIT_FAILURE);
      		}
      		if ((size_t) res == size) {
        	 return res;
      		}
      		current += res;
      		size -= res;
   	}

}

size_t readSomeTCPClient(TcpClient* tcpClient, uint8_t *buffer, size_t size) {

	int communicationSocket = tcpClient->socket;

    int res = recv(communicationSocket, buffer, size, 0);
    if (res < 0) {
         printf("Couldn't read to socket: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
      
    return res;
}



