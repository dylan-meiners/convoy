#ifndef SOCKUTIL_H
#define SOCKUTIL_H

#define _GNU_SOURCE

#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include "error.h"

typedef struct su_accept_resp {
    int c_fd;
    struct sockaddr_in* c_addr;
} su_accept_resp;

int su_socket(int, int, int);
int su_bind(int, int, uint32_t, int);
int su_listen(int, int);
su_accept_resp* su_accept(int);
int su_shutdown(int);
int su_close(int);
int su_write(int, const void*, size_t);
int su_getsockopt(int, int, int, void*, socklen_t*);
int su_connected(int);

#endif
