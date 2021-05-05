#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void error(const char*, int, int);
void _log(const char*, int, const char*, ...);

#endif
