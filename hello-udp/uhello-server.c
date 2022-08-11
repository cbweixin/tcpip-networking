//
// Created by wei,xin on 8/10/22.
//

#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 30

void error_handling(char *message);

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

