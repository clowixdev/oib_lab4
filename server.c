#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080

int main(int argc, char const* argv[]) {

    struct sockaddr_in address;
    bzero(&address, sizeof(address));

    printf("created serv_adress\n");

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &(address.sin_addr.s_addr));

    printf("filled address\n");

    int listener = socket(AF_INET, SOCK_STREAM, 0);

    printf("created listener\n");

    bind(listener, (struct sockaddr *)&address, sizeof(address));

    printf("bound listener to a address\n");

    listen(listener, 1);

    char serv_address[1024];
    bzero(serv_address, sizeof(serv_address));
    inet_ntop(AF_INET, &(address.sin_addr.s_addr), serv_address, sizeof(serv_address));
    printf("listening at %s:%d\n", serv_address, ntohs(address.sin_port));

    struct sockaddr_in client_address;
    socklen_t cadress_len = sizeof(client_address);
    int socket = accept(listener, (struct sockaddr *)&client_address, &cadress_len);

    printf("accepted connection\n");

    char buffer[1024] = "test_file.txt\0";
    int bytes_sent = 0;
    while (1) {
        bytes_sent = write(socket, buffer, sizeof(buffer));
        if (bytes_sent == -1) {
            perror("-1");
        } else {
            printf("sent %d bytes to client\n", bytes_sent);
            break;
        }
    }

    printf("server closing connection\n");
    close(listener);
    printf("connection closed - server\n");

    return 0;
}