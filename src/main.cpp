#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

const int PORT = 3000;
const int BACKLOG = 5; // the maximum number of pending connections
const int READ_BUFFER_SIZE = 1024;

int main(int argc, char *argv[]) {
    // Create a socket
    int server_fd; // fd means file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { // AF_INET: ipv4, SOCK_STREAM: TCP
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }
    // Bind a address to this socket
    struct sockaddr_in address{};
    int addr_len = sizeof(address);
    memset((char *) &address, 0, addr_len);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY means 0.0.0.0
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("cannot bind address to socket");
        exit(EXIT_FAILURE);
    }
    // Listen the incoming connection
    if (listen(server_fd, BACKLOG) < 0) {
        perror("failed to listen");
        exit(EXIT_FAILURE);
    }
    while (true) {
        int new_socket;
        // the accept function call will create a new socket for server to communicate with client
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addr_len)) < 0) {
            perror("failed to accept connection");
            exit(EXIT_FAILURE);
        }
        char buffer[READ_BUFFER_SIZE] = {0};
        if (read(new_socket, buffer, READ_BUFFER_SIZE) < 0) {
            printf("nothing to read");
        }
        write(new_socket, buffer, strlen(buffer));
        close(new_socket);
    }
}
