#pragma once

#define VERSION "v0.1.0"
#define VERSION_SHORT "v0.1"

#ifndef CELL_SIZE
#define CELL_SIZE 4
#endif

typedef void (*logprintf_t)(char *, ...);

extern logprintf_t logprintf;