//
// Created by wei,xin on 8/13/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int i;
    struct hostent *host;
    if (argc != 2) {
        printf("Usage : %s <addr>\n", argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);
    if (!host) {
        error_handling("gethost...error");
    }

    printf("Official name: %s \n", host->h_name);
    for (i = 0; host->h_aliases[i]; i++) {
        printf("Aliase %d : %s \n", i + 1, host->h_aliases[i]);
    }
    printf("Address type: %s \n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
    for (i = 0; host->h_addr_list[i]; i++) {
        // h_addr_list keep the address of in_addr struct instead of string, so need to do inet_ntoa conversion
        printf("IP addr %d : %s \n", i + 1, inet_ntoa(*(struct in_addr *) host->h_addr_list[i]));
    }
    return 0;

}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
