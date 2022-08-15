//
// Created by wei,xin on 8/15/22.
//

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int status;
    pid_t pid = fork();

    if (pid == 0) {
        sleep(15);
        return 24;
    } else {
        printf("child process pid: %d \n", pid);
        while (!waitpid(-1, &status, WNOHANG)) {
            sleep(3);
            puts("sleep 3sec.");
        }
    }
    if (WIFEXITED(status)) {
        printf("Child send %d \n", WEXITSTATUS(status));
    }
    return 0;
}