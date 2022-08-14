//
// Created by wei,xin on 8/13/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int server_sock, client_sock;
    FILE *fp;

    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    char buf[BUF_SIZE];

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("file_server.c", "rb");
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

    if (fp != NULL) {
        while (1) {
            // read BUF_SIZE(100) bytes each time
            size_t read_cnt = fread((void *) buf, 1, BUF_SIZE, fp);
            // if read bytes < buff size, means we hit the end of file
            if (read_cnt < BUF_SIZE) {
                write(client_sock, buf, read_cnt);
                break;
            }
            printf("begin to write\n");
            write(client_sock, buf, BUF_SIZE);
        }
    } else {
        printf("failed to find the file...");
    }

    // shutdown write buffer, but the remainning in write buffer would still be sent out
    shutdown(client_sock, SHUT_WR);
    // the read buff still on, so server still can recieve stream
    read(client_sock, buf, BUF_SIZE);
    printf("Message from client: %s \n", buf);

    fclose(fp);
    close(client_sock);
    close(server_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

