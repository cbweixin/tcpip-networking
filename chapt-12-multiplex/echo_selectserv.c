//
// Created by wei,xin on 8/16/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i, fd_max, fd_num;
    struct timeval timeout;
    fd_set reads, cpy_reads;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if (argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("bind() error");
    }
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;

    while (1) {
        cpy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1) {
            printf("failed to select() !\n");
            break;
        }
        // no event occured
        if (fd_num == 0) {
            continue;
        }

        for (int i = 0; i < fd_max + 1; ++i) {
            if (FD_ISSET(i, &cpy_reads)) {
                if (i == serv_sock) {
                    clnt_adr_sz = sizeof(clnt_adr);
                    clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &clnt_adr_sz);
                    if (clnt_sock == -1) {
                        printf("connect() error !\n");
                        continue;
                    }
                    FD_SET(clnt_sock, &reads);
                    if (fd_max < clnt_sock) {
                        fd_max = clnt_sock;
                    }
                    printf("connected client : %d \n", clnt_sock);
                } else { // read message
                    str_len = read(i, message, BUF_SIZE);
                    if (str_len == 0) { // if message from client is EOF
                        FD_CLR(i, &reads); // delete this socket id from fd_set, no monitor any more since closed
                        close(i);
                        printf("closed client: %d \n", i);
                    } else {
                        write(i, message, str_len); // echo
                    }
                }

            }

        }
    }

    close(serv_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
