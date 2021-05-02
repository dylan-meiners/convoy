#ifdef SERIAL_TEST

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "serial.h"
#include "error.h"

int main() {

    int arduino = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (arduino == -1) {

        error("open", errno, 1);
    }
    set_port_config(arduino, B115200);

    char* test_buf = (char*)malloc(sizeof(char) * 256);
    while (1) {

        //memset(test_buf, 0, sizeof(char) * 256);
        for (int i = 0; i < 256; i++) {

            test_buf[i] = 88;
        }
        char zero = 0;
        write(arduino, &zero, sizeof(char));
        usleep(100);
        char* recv = &zero;
        printf("Waiting for ack...\n");
        int num = read(arduino, recv, 1);
        if (*recv == 77) {
        
            printf("Recvd ack\n");
            write(arduino, test_buf, sizeof(char) * 256);
            usleep(256 * 100);
        }
        else {

            printf("Didn't recv ack; recvd: %d\n", (int)*recv);
        }
        printf("\n");
    }

    if (close(arduino) < 0) {

        fprintf(stderr, "ERROR %d: Unable to close arduino fd: %s\n", errno, strerror(errno));
        return -1;
    }

    return 0;
}

#endif
