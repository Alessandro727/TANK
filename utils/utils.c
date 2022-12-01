#include "utils.h"
#include <ifaddrs.h>

char* exec(const char* cmd) {

        FILE *fp;
        char* path = (char*) malloc(sizeof(char)*1035);

        /* Open the command for reading. */
        fp = popen(cmd, "r");


        if (fp == NULL) {
                printf("Failed to run command\n" );
                //exit(1);
        }

        int i = 0;
        int c;
        /* Read the output a line at a time - output it. */
        //while (fgets(path, sizeof(path), fp) != NULL) {
        while ((c = fgetc( fp )) != EOF) {
                path[i] = c;
                i++;
        }

        /* close */
        pclose(fp);

        return path;
}

int isLocal(const char* remoteIp) {

        char cmd[1035] = "ifconfig | egrep '";

        strcat(cmd,remoteIp);

        strcat(cmd,"'");

        char* result = exec(cmd);

	    if (strstr(result, remoteIp) != NULL) {
                return 1;
        }
        return 0;
}

char** getLocalIpList() {
	char** IpList = malloc(MAX_IP_ADDRESS_COUNT*sizeof(char*));
	for (int i =0 ; i < 50; ++i)
	        IpList[i] = malloc(16 * sizeof(char));
    struct ifaddrs * ifAddrStruct = NULL;
    void * tmpAddrPtr = NULL;
	int cont = 0;
    getifaddrs(&ifAddrStruct);

    for (struct ifaddrs * ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) {
            // NOLINTNEXTLINE
            tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            strcpy(IpList[cont], addressBuffer);
            cont += 1;
        }
    }
    if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
    return IpList;
}

void yield(int tries) {

    if (__builtin_expect(tries < 512, 1)) {
        // NOOP in 99% of the cases
    } else if (__builtin_expect(tries < 4096, 1)) {
        // pause in almost all useful cases
        _mm_pause();
    } else if (__builtin_expect(tries < 32768, 1)) {
        sched_yield();
    } else {
        usleep(1);
    }
}

void send_fd(int sock_descriptor, int fd) {

    struct msghdr msg = { 0 };
    struct cmsghdr *cmsg;
    int myfds[1];  /* Contains the file descriptors to pass */
    char iobuf[1];
    struct iovec io = {
            .iov_base = iobuf,
            .iov_len = sizeof(iobuf)
    };
    union {         /* Ancillary data buffer, wrapped in a union
                      in order to ensure it is suitably aligned */
        char buf[CMSG_SPACE(sizeof(myfds))];
        struct cmsghdr align;
    } u;

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = u.buf;
    msg.msg_controllen = sizeof(u.buf);
    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd));

    memcpy(CMSG_DATA(cmsg), &fd, sizeof(fd));

    if (sendmsg(sock_descriptor, &msg, 0) < 0) {
        perror("sendmsg() failed\n");
        printf("Errno is: %d\n", errno);
        exit(-1);
    }
}

int receive_fd(int sock_descriptor) {
    struct msghdr msg = { 0 };
    struct cmsghdr *cmsg;
    int myfds[1];  /* Contains the file descriptors to pass */
    char iobuf[1];
    struct iovec io = {
            .iov_base = iobuf,
            .iov_len = sizeof(iobuf)
    };
    union {         /* Ancillary data buffer, wrapped in a union
                      in order to ensure it is suitably aligned */
        char buf[CMSG_SPACE(sizeof(myfds))];
        struct cmsghdr align;
    } u;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = u.buf;
    msg.msg_controllen = sizeof(u.buf);

    while ( true ) {
        ssize_t rc = recvmsg(sock_descriptor, &msg, 0);
        if (rc < 0 && !(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINVAL)) {
            perror("recvmsg() failed\n");
            printf("Errno value: %d\n", errno);
        } else if (rc == 0 && !(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINVAL)) {
            printf("Invalid fd received\n");
            exit(-1);
        } else if (rc > 0 || errno == EINVAL) {
            break;
        }
    }
    cmsg = CMSG_FIRSTHDR(&msg);
    if (cmsg == NULL) {
        printf("receive_fd: invalid FD received\n");
    }
    int fd = *(int*)(CMSG_DATA(cmsg));
    return fd;
}

char** str_split(char* a_str, const char a_delim) {

    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int split(char *str, char c, char ***arr) {

    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}