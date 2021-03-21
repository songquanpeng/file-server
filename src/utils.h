#ifndef HTTP_SERVER_UTILS_H
#define HTTP_SERVER_UTILS_H

#include <cstdio>

// Print message and then exit with status 1.
void fatal(const char *msg) {
    perror(msg);
    exit(1);
}


#endif //HTTP_SERVER_UTILS_H
