//
// Created by wei,xin on 8/10/22.
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
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_size;

    struct sockaddr_in serv_adr, clnt_adr;
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // notice `SOCK_DGRAM`, this is different from TCP
    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1) {
        error_handling("UDP socket creation error");
    }
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    // udp has bind, but has no `connection` func call
    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("bind() error");
    }

    while (1) {
        clnt_adr_size = sizeof(clnt_adr);
        str_len = recvfrom(
                serv_sock, message, BUF_SIZE, 0, (struct sockaddr *) &clnt_adr, &clnt_adr_size
                          );
        message[str_len] = 0;
        if (str_len == 2 && (message[0] == 'q' || message[1] == 'Q')) {
            break;
        }
        // when call sendto, os would allocate IP and port
        sendto(
                serv_sock, message, str_len, 0, (struct sockaddr *) &clnt_adr, clnt_adr_size
              );

    }

    // the above while loop has no break, so this code would never got opportunity to execute
    close(serv_sock);
    return 0;
}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


