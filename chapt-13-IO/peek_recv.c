//
// Created by wei,xin on 8/17/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>
#include <fcntl.h>

#define BUF_SIZE 30

void error_handling(char *message);


int main(int argc, char *argv[]) {
    int acpt_sock, recv_sock;
    char message[BUF_SIZE];
    int str_len, i = 0, state;

    struct sockaddr_in serv_adr, acpt_adr;
    socklen_t serv_adr_sz;

    if (argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }


    acpt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (acpt_sock == -1) {
        error_handling("socket() error");
    }

    memset(&acpt_adr, 0, sizeof(acpt_adr));
    acpt_adr.sin_family = AF_INET;
    acpt_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    acpt_adr.sin_port = htons(atoi(argv[1]));

    if (bind(acpt_sock, (struct sockaddr *) &acpt_adr, sizeof(acpt_adr)) == -1) {
        error_handling("bind() error");
    }
    if (listen(acpt_sock, 5) == -1) {
        error_handling("listen() error");
    }

    serv_adr_sz = sizeof(serv_adr);
    recv_sock = accept(acpt_sock, (struct sockaddr *) &serv_adr, &serv_adr_sz);
    if (recv_sock == -1) {
        error_handling("accept() error");
    } else {
        printf("Connected client %d \n", ++i);
    }

    fcntl(recv_sock, F_SETOWN, getpid());
    state = sigaction(SIGURG, &act, 0);

    while ((str_len = read(recv_sock, message, BUF_SIZE)) != 0) {
        if (str_len == -1) {
            continue;
        }
        message[str_len] = 0;
        printf("message from client %s \n", message);
    }

    close(recv_sock);
    close(acpt_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

