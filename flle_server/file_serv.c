//
// Created by wei,xin on 8/8/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int server_sock;
    int client_sock;
    FILE *fp;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char read_buf[BUF_SIZE];
    char file_name[BUF_SIZE];

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

    // get the file name firstly
    ssize_t read_len = read(client_sock, file_name, BUF_SIZE);
    if (read_len == -1) {
        error_handling("read() error!");
    }
//    char *file_name;
    // get file_name
//    strcpy(file_name, read_buf);
    fp = fopen(file_name, "rb");
    if (fp != NULL) {
        while (1) {
            // read BUF_SIZE(100) bytes each time
            size_t read_cnt = fread((void *) read_buf, 1, BUF_SIZE, fp);
            // if read bytes < buff size, means we hit the end of file
            if (read_cnt < BUF_SIZE) {
                write(client_sock, read_buf, read_cnt);
                break;
            }
            write(client_sock, read_buf, BUF_SIZE);
        }
    }
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
