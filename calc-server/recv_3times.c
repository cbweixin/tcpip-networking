//
// Created by wei,xin on 8/8/22.
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
    int str_len;

    char msg1[] = "Hello server!";
    char msg2[] = "I'm client.";
    char msg3[] = "Nice to meet you too!";
    char *str_arr[] = {msg1, msg2, msg3};


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

    for (int i = 0; i < 3; i++) {
        ssize_t read_len = read(sock, (char *) (&strlen), 4);
        if (read_len == -1) {
            error_handling("read() error!");
        }
        read(sock, message, str_len);
        puts(message);

        str_len = strlen(str_arr[i]) + 1;
        write(sock, (char *) (&str_len), 4);
        write(sock, str_arr[i], str_len);

    }

    close(sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
