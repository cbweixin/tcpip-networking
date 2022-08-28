//
// Created by wei,xin on 8/27/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock, str_len;
    char message[BUF_SIZE];
    char message2[BUF_SIZE];
    struct sockaddr_in serv_adr;

    if (argc != 3) {
        printf("Usage : %s <IP> <PORT> \n", argv[0]);
        exit(1);
    }

    bzero(message, BUF_SIZE);
    bzero(message2, BUF_SIZE);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }
//    memset(&serv_adr, 0, sizeof(serv_adr));
    // using bzero instead of memset, more concise
    bzero(&serv_adr, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("connect() error !");
    } else {
        puts("Connected.........");
    }
    int n;
    if (n = recv(sock, message2, sizeof(message2), 0) > 0) {
        printf("Message %s: \n", message2);
    }

    while (1) {
        fputs("Input message(Q to quit): ", stdout);
        while ((n = read(stdin, message, sizeof(message))) > 0) {
            printf("mesage from terminal : %s \n", message);
        }
        if (send(sock, message, n, 0) < 0) {
            printf("send error! %s (errno :%d)\n", strerror(errno), errno);
            exit(0);

        }
        fgets(message, BUF_SIZE, stdin);

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }
        // tcp protocl 是没有边界的， 所以多次调用write的写入的字符串可能最终一次写入服务器
        // 那么read函数可能收到多次写入的字符串，而不是echo每次的写入
        write(sock, message, strlen(message));
        str_len = read(sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        printf("Mesage from server: %s \n", message);

    }
    close(sock);
    return 0;
}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
