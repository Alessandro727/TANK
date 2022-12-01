#include "../connections/P2PConnection.h"
#include "bench.h"

#define MESSAGES 1024 * 1024 * 1
//#define MESSAGES 1024

char* ip = "127.0.0.1";
char* port = "1234";

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Usage: %s <client / server> <(IP, optional) 127.0.0.1>\n", argv[0] );
        return -1;
    }
    bool isClient = argv[1][0] == 'c';
    if (argc > 2) {
        ip = argv[2];
    }

    printf("size, connection, messages, time, msgps, user, system, total\n");

    //int size[] = {1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u, 256u};
    int size[] = {16u};

    for (int j = 0; j < 9; j++) {

        char testdata[size[j]];
        for (int i = 0; i < size[j]; i++) {
            testdata[i] = (i % 256) + 12345;
        }
        //int* bebe = (int*) testdata;
        if (isClient) {

            char buf[size[j]];

            //sleep(2);

            //RdmaTransportClient* client = createRDMATransportClient();
            //connectRDMA(client, "127.0.0.1", "1234");

            ConnectionClient* client = createClient("127.0.0.1","127.0.0.1","1234","8239", RDMA);

            for (int k=0; k<MESSAGES; k++) {
	    		ClientWrite(client, testdata, size[j]);
	    		ClientRead(client,buf,size[j]);

    			for (int i = 0; i < size[j]; i++) {
    				//	printf("BUF = %d, i =%d\n", buu[i], i);
    					if (testdata[i] != buf[i]) {
    						printf("Error!! Testdata = %d, Buf2 = %d, i = %d\n", testdata[i], buf[i], i);
    					}

    			}
    			memset(buf, 0, size[j]);
    		}

            //benchClient(size[j], writeRDMAClient, client, testdata, size[j], MESSAGES);
            //benchClient(size[j], readRDMAClient, client, buf, size[j], MESSAGES);


        } else {
            char buf2[size[j]];

            //RdmaTransportServer* server = createRDMATransportServer("1234");
            //acceptRDMA(server);

            ConnectionServer* server = createServer("127.0.0.1","127.0.0.1","8239","1234", RDMA);

            //benchServer(size[j], readRDMAServer, server, buf2, size[j], MESSAGES);
            //benchServer(size[j], writeRDMAServer, server, buf2, size[j], MESSAGES);

            for (int k=0; k<MESSAGES; k++) {
                ServerRead(server, buf2, size[j]);
                ServerWrite(server,buf2,size[j]);


                for (int i = 0; i < size[j]; i++) {
                    if (testdata[i] != buf2[i]) {
                        printf("Error!! Testdata = %d, Buf2 = %d, i = %d\n", testdata[i], buf2[i], i);
                    }
                }

                memset(buf2, 0, size[j]);
            }

        }

    }
    return 0;

}

