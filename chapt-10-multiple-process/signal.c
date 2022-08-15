//
// Created by wei,xin on 8/15/22.
//

#include <sys/signal.h>
#include <stdio.h>
#include <unistd.h>

void timeout(int sig) {
    if (sig == SIGALRM) {
        puts("Time out!");
    }
    //every 2 sec, repeatly send alarm signal
    alarm(2);
}

void keycontrol(int sig) {
    if (sig == SIGINT) {
        puts("CTRL+C pressed");
    }
}

int main(int argc, char *argv[]) {
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for (i = 0; i < 3; i++) {
        puts("wait....");
        sleep(100);
    }
    return 0;
}

