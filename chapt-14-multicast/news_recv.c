//
// Created by wei,xin on 8/18/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int recv_sock;
    int str_len;
    char buf[BUF_SIZE];
    struct sockaddr_in adr;
    struct ip_mreq join_addr;
    if (argc != 3) {
        printf("Usage : %s <GroupIP> <PORT> \n", argv[0]);
        exit(1);
    }

    recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_port = htons(atoi(argv[2]));

    if (bind(recv_sock, (struct sockaddr *) &adr, sizeof(adr)) == -1) {
        error_handling("bind() error");
    }

    join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]);
    join_addr.imr_interface.s_addr = htonl(INADDR_ANY);

    int state = setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &join_addr, sizeof(join_addr));
    if (state) {
        error_handling("set socket option error !");
    }

    while (1) {
        str_len = recvfrom(recv_sock, buf, BUF_SIZE - 1, 0, NULL, 0);
        if (str_len < 0) {
            break;
        }
        buf[str_len] = 0;
        fputs(buf, stdout);
    }
    close(recv_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
