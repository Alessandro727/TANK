#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <assert.h>
#include <sched.h>
#include <errno.h>
#include <immintrin.h>

#define MAX_IP_ADDRESS_COUNT 50

#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

char* exec(const char*);

int isLocal(const char*);

char** getLocalIpList();

void yield(int);

void send_fd(int, int);

int receive_fd(int);

char** str_split(char*, const char);

int split(char*, char, char***);

#ifdef __cplusplus
}
#endif

#endif
