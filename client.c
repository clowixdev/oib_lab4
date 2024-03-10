#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const* argv[]) {

    struct sockaddr_in address; 
    bzero(&address, sizeof(address));

    printf("created serv_adress\n");

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &(address.sin_addr.s_addr));

    printf("filled address\n");

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    printf("created socket\n");

    bind(sock, (struct sockaddr *)&address, sizeof(address));

    printf("binded socket to port\n");

    while (1) {
        if (connect(sock, (struct sockaddr *)&address, sizeof(address)) == 0) {
            printf("connected\n");
            break;
        } else {
            char serv_address[1024];
            bzero(serv_address, sizeof(serv_address));
            inet_ntop(AF_INET, &(address.sin_addr.s_addr), serv_address, sizeof(serv_address));
            printf("trying to connect to at %s:%d\n", serv_address, ntohs(address.sin_port));
            sleep(1);
        }
    }

    char fname_recv_buffer[1024];

    while (1) {
        bzero(fname_recv_buffer, sizeof(fname_recv_buffer));
        if (read(sock, fname_recv_buffer, sizeof(fname_recv_buffer))) {
            printf("Recieved from server: %s\n", fname_recv_buffer);
            break;
        } else {
            printf("recieved nothing...\n\n");
        }
    }

    printf("client closing connection\n");
    close(sock);
    printf("connection closed - client\n");

    return 0;
}