//
// Created by wei,xin on 8/11/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    char message[BUF_SIZE];
    int str_len, i;
    socklen_t adr_sz;

    struct sockaddr_in my_adr, your_adr;
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        error_handling("UDP socket creation error");
    }
    memset(&my_adr, 0, sizeof(my_adr));
    my_adr.sin_family = AF_INET;
    my_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_adr.sin_port = htons(atoi(argv[1]));

    // udp has bind, but has no `connection` func call
    if (bind(sock, (struct sockaddr *) &my_adr, sizeof(my_adr)) == -1) {
        error_handling("bind() error");
    }

    for (i = 0; i < 3; i++) {
        sleep(5);
        adr_sz = sizeof(your_adr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr *) &your_adr, &adr_sz);
        printf("Message %d: %s, size : %d\n", i + 1, message, str_len);
    }
    close(sock);
    return 0;
}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
