//
// Created by wei,xin on 8/28/22.
//

#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

#define NUM 1024

int mystrtok(char *argv[], char *string) {

    int i = 0, status;
    char delim[] = " ";
    char *p;
    // strtok - string token, split string by token
    argv[0] = strtok(string, delim);
    while (argv[i] != NULL) {
        argv[++i] = strtok(NULL, delim);
        printf("%d is %s\n", i, argv[i]);
    }

    return 0;
}

int main() {

    char str[NUM];
    int status;
    pid_t pid;
    char *argv[NUM];

    // ❯ gcc fork_test.c -o ft.out
    //❯ ./ft.out la /
    //
    //warning: this program uses gets(), which is unsafe.
    //$:la /
    //1 is /
    //2 is (null)
    //
    //$:find / -type f -iname "*.a"
    //1 is /
    //2 is -type
    //3 is f
    //4 is -iname
    //5 is "*.a"
    //6 is (null)
    //
    //$:
    // parse the command line
    while (1) {
        printf("\n$:");
        gets(str);
        status = mystrtok(argv, str);
        if (status != 0) {
            printf("fail to get command!\n");
        }

        pid = fork();

        if (pid == -1) printf("fork failure!\n");
        else if (pid == 0) {
            execv(argv[0], argv);
        } else {
            wait(&status);
        }
    }

}