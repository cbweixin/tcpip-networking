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
        calc-server/op_client.c
        calc-server/op_server.c
        hello-server/hello_client2.c
        hello-server/hello_server3.c
        hello-server/hello_client3.c
        calc-server/send_3times.c
        calc-server/recv_3times.c
        flle_server/file_serv.c
        flle_server/file_clnt.c
        hello-udp/uhello-server.c
        hello-udp/uhello-client.c
        bounded-udp/bound_host1.c
        bounded-udp/bound_host2.c
        bounded-udp/chat-srv-udp.c
        bounded-udp/chat-cln-udp.c
        chapt-7/file_server.c
        chapt-7/file_client.c
        chapt-8-dns/gethostbyname.c
        chapt-8-dns/gethostbyaddr.c
        chapt-9-socket-options/sock_type.c
        chapt-9-socket-options/get_buf.c
        chapt-9-socket-options/set_buf.c
        chapt-9-socket-options/reuseadr_eserver.c
        chapt-10-multiple-process/fork.c
        chapt-10-multiple-process/zoombie.c
        chapt-10-multiple-process/wait.c
        chapt-10-multiple-process/waitpid.c
        chapt-10-multiple-process/signal.c
        chapt-10-multiple-process/sigaction.c
        chapt-10-multiple-process/remove_zoombie.c
        chapt-10-multiple-process/echo_mpserv.c
        chapt-10-multiple-process/echo_mpclient.c
        chapt-11-IPC/pipe1.c
        chapt-11-IPC/pip2.c chapt-11-IPC/pipe3.c chapt-11-IPC/echo_storeserv.c chapt-12-multiplex/select.c chapt-12-multiplex/echo_selectserv.c chapt-13-IO/oob_send.c chapt-13-IO/oob_recv.c chapt-13-IO/peek_send.c chapt-13-IO/peek_recv.c)
