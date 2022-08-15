//
// Created by wei,xin on 8/15/22.
//

#include <unistd.h>
#include <stdio.h>

// global var
int gval = 10;

int main(int argc, char *argv[]) {
    pid_t pid;
    // local var
    int lval = 20;
    gval++;
    lval += 5;
    pid = fork();
    if (pid == 0) { // child process
        gval += 2;
        lval += 2;
    } else { // parent process
        gval -= 2;
        lval -= 2;
    }

    if (pid == 0) {
        printf("Child PRoc: [%d, %d] \n", gval, lval);
    } else {
        printf("Parent Proc: [%d, %d] \n", gval, lval);
    }
}
