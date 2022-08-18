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

void urg_handler(int signo);

int acpt_sock, recv_sock;

int main(int argc, char *argv[]) {
    char message[BUF_SIZE];
    int str_len, i = 0, state;

    struct sockaddr_in serv_adr, recv_adr;
    socklen_t serv_adr_sz;
    struct sigaction act;

    if (argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    acpt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (acpt_sock == -1) {
        error_handling("socket() error");
    }

    memset(&recv_adr, 0, sizeof(recv_adr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(acpt_sock, (struct sockaddr *) &recv_adr, sizeof(recv_adr)) == -1) {
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

void urg_handler(int signo) {
    int str_len;
    char buf[BUF_SIZE];
    // TODO: why need -1?
    str_len = recv(recv_sock, buf, sizeof(buf) - 1, MSG_OOB);
//    str_len = recv(recv_sock, buf, 1, MSG_OOB);
    printf("sizeof(buf) : %lu \n", sizeof(buf));
//    str_len = recv(recv_sock, buf, sizeof(buf), MSG_OOB);
    buf[str_len] = 0;
    printf("Urgent message: %s \n", buf);
}
