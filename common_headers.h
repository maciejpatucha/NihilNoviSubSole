#ifndef COMMON_HEADERS_H
#define COMMON_HEADERS_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "logging.h"

typedef enum {
    FOREGROUND,
    BACKGROUND
} runningMode;

runningMode rMode;

#endif // COMMON_HEADERS_H

