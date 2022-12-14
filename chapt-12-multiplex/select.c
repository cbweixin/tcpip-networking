//
// Created by wei,xin on 8/16/22.
//

#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]) {
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&reads);
    // fd 0 is stdin, monitoring stdin event
    FD_SET(0, &reads);

    // should not set timeout here, each time call select func, you need to set it
//    timeout.tv_sec = 5;
//    timeout.tv_usec = 5000;

    while (1) {
        // copy reads, general pattern, so reads still has intitial value. after call select, except the fd which
        // has event , all other fds would be reset to 0
        temps = reads;
        // set it
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1, &temps, 0, 0, &timeout);
        printf("result is : %d \n", result);
        if (result == -1) {
            puts("select() error !");
            break;
        } else if (result == 0) {
            puts("Time-out!");
        } else {
            if (FD_ISSET(0, &temps)) {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console: %s", buf);
            }
        }

    }
    return 0;

}
