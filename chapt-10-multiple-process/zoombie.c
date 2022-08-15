//
// Created by wei,xin on 8/15/22.
//

#include <stdio.h>
#include <unistd.h>

// 孤儿进程：一个父进程退出，而它的一个或多个子进程还在运行，那么那些子进程将成为孤儿进程。孤儿进程将被init进程(进程号为1)所收养，并由init
// 进程对它们完成状态收集工作。
//
//僵尸进程：一个进程使用fork创建子进程，如果子进程退出，而父进程并没有调用wait或waitpid获取子进程的状态信息，那么子进程的进程描述符仍然保存
// 在系统中。这种进程称之为僵死进程。

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        puts("Hi, I am a child process");
    } else {
        printf("Child process ID: %d \n", pid);
        sleep(30);
    }
    if (pid == 0) {
        puts("End child process");

    } else {
        puts("End parent process");
    }
    return 0;
}
