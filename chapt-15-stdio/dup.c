//
// Created by wei,xin on 8/19/22.
//

#include <unistd.h>
#include <printf.h>

int main(int argc, char *argv[]) {
    int cfd1, cfd2;
    char str1[] = "Hi! \n";
    char str2[] = "It's a nice day!@ \n";
    // clone file descriptor of stdin
    cfd1 = dup(1);
    cfd2 = dup2(cfd1, 7);

    printf("fd1=%d, fd2=%d \n", cfd1, cfd2);
    write(cfd1, str1, sizeof(str1));
    write(cfd2, str2, sizeof(str2));

    // close cloned fd won't close the file or socket
    close(cfd1);
    close(cfd2);

    write(1, str1, sizeof(str1));
    close(1);
    write(1, str1, sizeof(str1));
    // all fd of stdin would be closed
    close(1);
    // since fd-1 stdin is closed already, below will not work
    write(1, str2, sizeof(str2));
    return 0;
}
