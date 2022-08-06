cmake_minimum_required(VERSION 3.22)
project(tcpip_networking C)

set(CMAKE_C_STANDARD 11)

add_executable(
        tcpip_networking main.c
        hello-server/hello_server.c
        hello-server/hello_client.c
        hello-server/endian_conv.c
        hello-server/inet_addr.c
        hello-server/inet_aton.c
        hello-server/inet_ntoa.c
        echo-server/echo_server.c
        echo-server/echo_client.c
        echo-server/echo_client_enhanced.c
)
