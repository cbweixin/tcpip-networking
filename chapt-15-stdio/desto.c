//
// Created by wei,xin on 8/18/22.
//

#include <stdio.h>
#include <sys/fcntl.h>

int main(void) {
    FILE *fp;
    int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        fputs("file open error", stdout);
        return -1;
    }

    // convert file descriptor to FILE pointer
    fp = fdopen(fd, "w");
    // standardized IO, could util io buffer
    fputs("Network c programming \n", fp);
    // close the FILE pointer, so file descriptor is no need to close any more.
    fclose(fp);
    return 0;
}