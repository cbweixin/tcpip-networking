//
// Created by wei,xin on 8/16/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

void error_handling(char *message);

void read_routine(int sock, char *buf);

void write_routine(int sock, char *buf);

//  ./treeps | grep mpc.out
//                |_ 71127    grep --color=auto mpc.out
//          |_ 70299    ./mpc.out 127.0.0.1 19999
//             |_ 70300    ./mpc.out 127.0.0.1 19999
//          |_ 69289    ./mpc.out 127.0.0.1 19999
//             |_ 69290    ./mpc.out 127.0.0.1 19999
//             |_ 69332    ./mpc.out 127.0.0.1 19999
//                |_ 69333    ./mpc.out 127.0.0.1 19999
//❯ ./treeps | grep em.out
//                |_ 71184    grep --color=auto em.out
//                |_ 69134    ./em.out 19999
//                   |_ 69291    ./em.out 19999
//                   |_ 69334    ./em.out 19999
//                   |_ 70301    ./em.out 19999

int main(int argc, char *argv[]) {
    int sock, str_len, recv_len, recv_cnt;
    char message[BUF_SIZE];
    struct sockaddr_in serv_adr;
    pid_t pid;

    if (argc != 3) {
        printf("Usage : %s <IP> <PORT> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("connect() error !");
    } else {
        puts("Connected.........");
    }

    pid = fork();
    if (pid == 0) { // child proc responsible for writing
        write_routine(sock, message);
    } else { // main proc(parent) responsible for reading
        read_routine(sock, message);
    }
    close(sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_routine(int sock, char *buf) {
    while (1) {
        int str_len = read(sock, buf, BUF_SIZE - 1);
        if (str_len == 0) {
            return;
        }
        buf[str_len] = 0;
        printf("Mesage from server: %s \n", buf);
    }
}

void write_routine(int sock, char *buf) {
    while (1) {
        fputs("Input message(Q to quit): ", stdout);
        fgets(buf, BUF_SIZE, stdin);

        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
            // why not use close? after we do fork, the fd of socket got copied, so close won't really close
            // the socket, we need shutdown here
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buf, BUF_SIZE - 1);
    }
}
