#include "socketutil.h"

int su_socket(int domain, int type, int protocol) {

    int fd = socket(domain, type, protocol);
    if (fd < 0) {

        error(__FUNCTION__, errno, 1);
        return -1;
    }
    return fd;
}

int su_bind(int fd, int family, uint32_t addr, int port) {

    struct sockaddr_in in;
    memset(&in, 0, sizeof(in));
    in.sin_family = family;
    in.sin_addr.s_addr = addr;
    in.sin_port = htons(port);
    int result = bind(fd, (struct sockaddr*)&in, sizeof(in));
    if (result < 0) {

        error(__FUNCTION__, errno, 1);
        return -1;
    }
    return 1;
}

int su_listen(int fd, int max_connects) {

    int result = listen(fd, max_connects);
    if (result < 0) {

        error(__FUNCTION__, errno, 1);
        return -1;
    }
    return 1;
}

su_accept_resp* su_accept(int fd) {
    struct sockaddr_in caddr;
    int len = sizeof(caddr);
    int new_fd = accept(fd, (struct sockaddr*)&caddr, &len);
    if (new_fd < 0) {

        error(__FUNCTION__, errno, 1);
        return NULL;
    }
    su_accept_resp* result = (su_accept_resp*)malloc(sizeof(su_accept_resp));
    result->c_fd = new_fd;
    result->c_addr = &caddr;
    return result;
}

int su_shutdown(int fd) {

    int result = shutdown(fd, SHUT_RDWR);
    if (result < 0) {

        error(__FUNCTION__, errno, 0);
        return -1;
    }
    return 1;
}

int su_close(int fd) {

    int result = close(fd);
    if (result < 0) {

        error(__FUNCTION__, errno, 0);
        return -1;
    }
    return 1;
}

int su_write(int fd, const void* data, size_t size) {

    int result = write(fd, data, size);
    if (result < 0) {
            
        error(__FUNCTION__, errno, 0);
        return -1;
    }
    usleep(100 * size);
    return 1;
}