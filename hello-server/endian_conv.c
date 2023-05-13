//
// Created by wei,xin on 8/4/22.
//

#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr=0x12345678;
    unsigned long net_addr;

    net_port=htons(host_port);
    net_addr= htonl(host_addr);

    printf("Host ordered port : %#x \n", host_port);
    printf("[0]:0x%x\n", *((char *)&host_port + 0));
    printf("[1]:0x%x\n", *((char *)&host_port + 1));

    printf("network ordered port : %#x \n", net_port);
    printf("[0]:0x%x\n", *((char *)&net_port + 0));
    printf("[1]:0x%x\n", *((char *)&net_port + 1));

    printf("Host ordered addr : %#lx \n", host_addr);
    printf("[0]:0x%x\n", *((char *)&host_addr + 0));
    printf("[1]:0x%x\n", *((char *)&host_addr + 1));
    printf("[2]:0x%x\n", *((char *)&host_addr + 2));
    printf("[3]:0x%x\n", *((char *)&host_addr + 3));


    printf("network ordered addr : %#lx \n", net_addr);
    printf("[0]:0x%x\n", *((char *)&net_addr + 0));
    printf("[1]:0x%x\n", *((char *)&net_addr + 1));
    printf("[2]:0x%x\n", *((char *)&net_addr + 2));
    printf("[3]:0x%x\n", *((char *)&net_addr + 3));
}
