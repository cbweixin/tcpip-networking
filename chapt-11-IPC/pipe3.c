//
// Created by wei,xin on 8/16/22.
//

#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]) {
    int fds1[2], fds2[2];
    char str1[] = "Who are you?";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;

    // using 2 pipe
    pipe(fds1);
    pipe(fds2);

    pid = fork();
    if (pid == 0) { // child proc bidirection communication
        write(fds1[1], str1, sizeof(str1));
        // need sleep , otherwise, read would get the data write by itsef , then parent proc would waiting forever
        read(fds2[0], buf, BUF_SIZE);
        printf("Child proc output: %s \n", buf);
    } else {  // parent proc bidirectional communication
        read(fds1[0], buf, BUF_SIZE);
        printf("Parent proc output: %s \n", buf);
        write(fds2[1], str2, sizeof(str2));
//        sleep(3);
    }

    return 0;
}

