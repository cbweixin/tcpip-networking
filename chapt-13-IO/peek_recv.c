//
// Created by wei,xin on 8/17/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUF_SIZE 30

void error_handling(char *message);


int main(int argc, char *argv[]) {
    int acpt_sock, recv_sock;
    char message[BUF_SIZE];
    int str_len, i = 0, state;

    struct sockaddr_in recv_adr, acpt_adr;
    socklen_t recv_adr_sz;

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

    recv_adr_sz = sizeof(recv_adr);
    recv_sock = accept(acpt_sock, (struct sockaddr *) &recv_adr, &recv_adr_sz);
    if (recv_sock == -1) {
        error_handling("accept() error");
    } else {
        printf("Connected client %d \n", ++i);
    }

    while (1) {
        str_len = recv(recv_sock, message, sizeof(message) - 1, MSG_PEEK | MSG_DONTWAIT);
        if (str_len > 0) {
            break;
        }
    }
    message[str_len] = 0;
    printf("buffering %d bytes: %s \n", str_len, message);

    str_len = recv(recv_sock, message, sizeof(message) - 1, 0);
    if (str_len == -1) {
        printf("failed to recieve again...");
    }
    message[str_len] = 0;
    printf("read again: %s \n", message);


    close(recv_sock);
    close(acpt_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

