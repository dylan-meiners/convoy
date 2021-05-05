#include "error.h"

void error(const char* func, int err, int kill) {

    char str[100] = { 0 };
    strcat(str, "ERROR: %d: ");
    strcat(str, func);
    strcat(str, ": %s\n");
    fprintf(stderr, str, err, strerror(err));
    if (kill) exit(-1);
}

void _log(const char* name, int ident, const char* format, ...) {

	va_list args;
	printf("[%s][%d]: ", name, ident);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\n");
}
