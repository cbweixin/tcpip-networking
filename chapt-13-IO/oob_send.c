//
// Created by wei,xin on 8/17/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in recv_adr;
    if (argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&recv_adr, 0, sizeof(recv_adr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *) &recv_adr, sizeof(recv_adr)) == -1) {
        error_handling("connect() error !");
    } else {
        puts("Connected.........");
    }

    write(sock, "123\n", strlen("123\n"));
    send(sock, "4\n", strlen("4\n"), MSG_OOB);
//    send(sock, "4\n", strlen("4\n"), MSG_DONTWAIT);
    send(sock, "5\n", strlen("5\n"), MSG_DONTWAIT);
    write(sock, "567\n", strlen("567\n"));
    // need strlen()+1, otherwise it only prints "89" instead of "890"
    send(sock, "890\n", strlen("890\n"), MSG_OOB);

    close(sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
