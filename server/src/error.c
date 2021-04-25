#include "error.h"

void error(const char* func, int err, int kill) {

    char str[100] = { 0 };
    strcat(str, "ERROR: %d: ");
    strcat(str, func);
    strcat(str, ": %s\n");
    fprintf(stderr, str, err, strerror(err));
    if (kill) exit(-1);
}