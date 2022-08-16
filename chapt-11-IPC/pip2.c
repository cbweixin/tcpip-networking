//
// Created by wei,xin on 8/16/22.
//

#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]) {
    int fds[2];
    char str1[] = "Who are you?";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();
    if (pid == 0) { // child proc bidirection communication
        write(fds[1], str1, sizeof(str1));
        sleep(2);
        read(fds[0], buf, BUF_SIZE);
        printf("Child proc output: %s \n", buf);
    } else {  // parent proc bidirectional communication
        read(fds[0], buf, BUF_SIZE);
        printf("Parent proc output: %s \n", buf);
        write(fds[1], str2, sizeof(str2));
        sleep(3);
    }

    return 0;
}

