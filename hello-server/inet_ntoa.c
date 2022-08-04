//
// Created by wei,xin on 8/4/22.
//
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);

    // notice, this function would return a pointer
    // after you got this pointer, you need to copy the value to your own address
    // otherwise, after next call, the pointer would be overwrite with new value
    // str_ptr now has value 1.2.3.4
    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation1: %s \n", str_ptr);

    // call again, now str_ptr changed to 1.1.1.1
    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2: %s \n", str_ptr);
    // str_arr still 1.2.3.4
    printf("Dotted-Decimal notation3: %s \n", str_arr);

    return 0;
}
