//
// Created by wei,xin on 8/7/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len = 0;
    int idx = 0;

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

    // busy waiting, client would delay the execution of read, and wait the server
    // write complete response , then just read in one shot.
    for (idx = 0; idx < 3000; idx++) {
        printf("Wait time %d", idx);
    }
    read(sock, message, sizeof(message));
    printf("Message from server : %s \n", message);
    printf("Function read call count : %d \n", str_len);
    close(sock);
    return 0;
}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
