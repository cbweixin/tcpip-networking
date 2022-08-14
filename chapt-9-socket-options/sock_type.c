//
// Created by wei,xin on 8/13/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int tcp_sock, udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;

    optlen = sizeof(sock_type);
    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
    printf("Sock_stream: %d \n", tcp_sock);
    printf("Sock_Dgram: %d \n", udp_sock);

    state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void *) &sock_type, &optlen);
    if (state) {
        error_handling("getsockopt() error!");
    }
    printf("Scoket type one : %d\n", sock_type);

    state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void *) &sock_type, &optlen);
    if (state) {
        error_handling("getsockopt() error!");
    }
    printf("Scoket type two : %d\n", sock_type);
    return 0;

}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
