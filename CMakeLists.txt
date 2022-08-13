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
        hello-server/hello_server2.c
        echo-server/echo_server.c
        echo-server/echo_client.c
        echo-server/echo_client_enhanced.c
        calc-server/op_client.c calc-server/op_server.c hello-server/hello_client2.c hello-server/hello_server3.c hello-server/hello_client3.c calc-server/send_3times.c calc-server/recv_3times.c flle_server/file_serv.c flle_server/file_clnt.c hello-udp/uhello-server.c hello-udp/uhello-client.c bounded-udp/bound_host1.c bounded-udp/bound_host2.c bounded-udp/chat-srv-udp.c)
