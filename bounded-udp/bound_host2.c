//
// Created by wei,xin on 8/11/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    char msg1[] = "Hi!";
    char msg2[] = "I am another UDP host!";
    char msg3[] = "Nice to meet you";
    socklen_t your_adr_sz;

    struct sockaddr_in you_adr;
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        error_handling("UDP socket creation error");
    }
    memset(&you_adr, 0, sizeof(you_adr));
    you_adr.sin_family = AF_INET;
    you_adr.sin_addr.s_addr = inet_addr(argv[1]);
    you_adr.sin_port = htons(atoi(argv[2]));

    sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr *) &you_adr, sizeof(you_adr));
    sendto(sock, msg2, sizeof(msg1), 0, (struct sockaddr *) &you_adr, sizeof(you_adr));
    sendto(sock, msg3, sizeof(msg1), 0, (struct sockaddr *) &you_adr, sizeof(you_adr));

    close(sock);
    return 0;
}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

