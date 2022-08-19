//
// Created by wei,xin on 8/18/22.
//

#include <stdio.h>
#include <sys/fcntl.h>

int main(void) {
    FILE *fp;
    int fd = open("data1.dat", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        fputs("file open error", stdout);
        return -1;
    }

    printf("First file descriptor: %d \n", fd);
    fp = fdopen(fd, "w");
    fputs("TCP/IP Socket Programming \n", fp);
    // fileno(fp), convert FILE pointer to file descriptor
    printf("Second file descriptor: %d \n", fileno(fp));
    fclose(fp);
    return 0;
}
