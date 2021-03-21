#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <thread>
#include <cstdlib>
#include "utils.h"
#include "server.h"
#include "constants.h"

using namespace std;

int main(int argc, char *argv[]) {
    int server_fd = initialize_server(PORT);
    printf("[Log] Server is listening on port %d.\n", PORT);

    struct sockaddr_in address{};
    int addr_len = sizeof(address);
    memset((char *) &address, 0, sizeof(address));

    while (true) {
        int client_socket;
        if ((client_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addr_len)) < 0) {
            printf("[Warning] Failed to accept connection.");
        }
        printf("[Log] New connection with socket file descriptor: %d.\n", client_socket);
        thread thread(process_request, client_socket);
        thread.detach();
    }
}
