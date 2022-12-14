//
// Created by wei,xin on 8/2/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


void error_handling(char *message);

int main(int argc, char *argv[]) {
    int server_sock;
    int client_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "hello world!";
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    // step 1: create socket
    // PF_INET IPV4, one of Protocl Family
    // SOCK_STREAM 面向连接的套接字
    server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        error_handling("socket() error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    // step 2 : bind address and port
    serv_addr.sin_family = AF_INET;
    // INADDR_ANY, constant number, automatically retrieve the server ip, no need to manually input
    // even if the server has multiple ip, such as router, if the port is correct, then client could use any ip
    // to communicate
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(server_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    // step 3 : start listening
    // 5 - backlog, ie, 请求等待队列
    if (listen(server_sock, 5) == -1) {
        error_handling("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    // step 4 : accepting request
    client_sock = accept(server_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
    if (client_sock == -1) {
        error_handling("accept() error");
    }

    // now connection established, we can
    // step 5: write response
    int idx = 0;
    while (idx < strlen(message)) {
//        write(client_sock, (char *) &message[idx++], sizeof(message[idx - 1]));
        write(client_sock, message + (idx++), sizeof(message[idx - 1]));
    }
    close(client_sock);
    close(server_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
