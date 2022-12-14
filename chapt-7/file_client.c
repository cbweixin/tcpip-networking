//
// Created by wei,xin on 8/13/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 100

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    int read_cnt;

    char buf[BUF_SIZE];

    if (argc != 3) {
        printf("Usage : %s <IP> <Port>\n", argv[0]);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("sock() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // when client make connection, the kernal would allocate ip and port for client,
    // hence client no need to do `bind` as server does
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error!");
    }

    FILE *fp = fopen("download.txt", "wb");

    while ((read_cnt = read(sock, buf, BUF_SIZE)) != 0) {
        fwrite((void *) buf, 1, read_cnt, fp);
    }

    puts("Received file data");
    write(sock, "Thank you", 10);
    fclose(fp);
    close(sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

