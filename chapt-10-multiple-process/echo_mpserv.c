//
// Created by wei,xin on 8/15/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>
// try to set to 30, it gives me error, this size need to be consistent with client setting
// I use echo_client_enhanced.c as client, the setting is 1024, so server need to be the same
#define BUF_SIZE 1024

void error_handling(char *message);

void read_childproc(int sig);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i, state;
    i = 0;

    pid_t pid;
    struct sigaction act;


    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if (argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);

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
    while (1) {
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &clnt_adr_sz);
        if (clnt_sock == -1) {
//            error_handling("accept() error");
            printf("accept error...");
            continue;
        } else {
            printf("Connected client %d \n", i++);
        }
        pid = fork();
        if (pid == -1) {
            puts("fork failed...");
            close(clnt_sock);
            continue;
        }
        if (pid == 0) { // child proc execution
            close(serv_sock); // why close it? because child proc already got cloned serv_sock from parent proc
            while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0) {
                printf("msg received : %s\n", message);
                write(clnt_sock, message, str_len);
            }
            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        } else {
            printf("child proc id: %d \n", pid);
            close(clnt_sock); // clnt sock already cloned for child proc, so sever need destory its own clnt_sock
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

void read_childproc(int sig) {
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
        printf("Removed proc id: %d \n", id);
        printf("Child send: %d \n", WEXITSTATUS(status));
    }
}
