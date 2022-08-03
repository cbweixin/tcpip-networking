cmake_minimum_required(VERSION 3.22)
project(tcpip_networking C)

set(CMAKE_C_STANDARD 11)

add_executable(tcpip_networking main.c hello-server/hello_server.c hello-server/hello_client.c)
