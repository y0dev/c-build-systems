#include <stdio.h>

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif

void print_debug(const char *message);

#endif // DEBUG_H
