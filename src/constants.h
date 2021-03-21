#ifndef HTTP_SERVER_CONSTANTS_H
#define HTTP_SERVER_CONSTANTS_H

const int PORT = 3000;
const char * SERVER_NAME = "JustSong's HTTP Server";
const char * HTTP_VERSION = "HTTP/1.0";
// The maximum number of pending connections
const int BACKLOG = 5;
const int READ_BUFFER_SIZE = 1024;

#endif //HTTP_SERVER_CONSTANTS_H
