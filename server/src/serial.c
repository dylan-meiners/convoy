#include "../include/serial.h"
#include <termios.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int set_port_config(int fd, int speed) {

    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {

        fprintf(stderr, "ERROR %d: Unable to get tty attrs from file descriptor: %s\n", errno, strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag &=      ~(PARENB | PARODD);
    tty.c_cflag &=      ~CSTOPB;
    tty.c_cflag &=      ~CSIZE;
    tty.c_cflag |=       CS8;
    tty.c_cflag &=      ~CRTSCTS;
    tty.c_cflag |=       CREAD | CLOCAL;

    tty.c_lflag &=      ~ICANON;
    tty.c_lflag &=      ~ECHO;
    tty.c_lflag &=      ~ECHOE;
    tty.c_lflag &=      ~ECHONL;
    tty.c_lflag &=      ~ISIG;

    tty.c_iflag &=      ~(IXON | IXOFF | IXANY);
    tty.c_iflag &=      ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    
    tty.c_oflag &=      ~OPOST;
    tty.c_oflag &=      ~ONLCR;

    tty.c_cc[VMIN] =    0;
    tty.c_cc[VTIME] =   10;

    if(tcsetattr(fd, TCSANOW, &tty) != 0) {

        fprintf(stderr, "ERROR %d: Unable to set tty attrs: %s\n", errno, strerror(errno));
        return -1;
    }

    return 0;
}