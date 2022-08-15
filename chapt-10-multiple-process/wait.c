//
// Created by wei,xin on 8/15/22.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int status;
    pid_t pid = fork(); // child 1

    if (pid == 0) {
        return 3;
    } else {
        printf("Child PID: %d \n", pid);
        pid = fork();
        if (pid == 0) { // chiild 2
            exit(7);
        } else {
            printf("Child pid: %d \n", pid);
            wait(&status); // need to call 2 times since we create 2 children
            if (WIFEXITED(status)) {
                printf("Child send one: %d \n", WEXITSTATUS(status));
            }

            wait(&status);
            if (WIFEXITED(status)) {
                printf("Child send two: %d \n", WEXITSTATUS(status));
            }
            sleep(30);
        }

    }

    return 0;
}
