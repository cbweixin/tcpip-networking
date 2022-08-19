//
// Created by wei,xin on 8/19/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE] = {0,};
    int i = 0;
    FILE *readfp, *writefp;

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

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &clnt_adr_sz);
    if (clnt_sock == -1) {
        error_handling("accept() error");
    } else {
        printf("Connected client %d \n", i + 1);
    }

    // convert fd to file pointer
    readfp = fdopen(clnt_sock, "r");
    // notice dup function call, now writefp has a clone fd for socket
    writefp = fdopen(dup(clnt_sock), "w");
    fputs("From server: Hi~ client? \n", writefp);
    fputs("I love all of the world \n", writefp);
    fputs("you are welcome! \n", writefp);
    fflush(writefp);

    // critical, socket goes to half-close status because this call
    shutdown(fileno(writefp), SHUT_WR);

    // fclose would send EOF to client
    fclose(writefp);
    // will server get last message from client after close fclose on writefp?
    fgets(message, sizeof(message), readfp);
    fputs(message, stdout);
    fclose(readfp);

//    close(serv_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
