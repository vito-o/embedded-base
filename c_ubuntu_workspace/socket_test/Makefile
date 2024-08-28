CC:=gcc
.PHONY: single_conn single_conn_clean
.PHONY: multi_conn multi_conn_clean
.PHONY: multi_conn_pro multi_conn_pro_clean
.PHONY: udp_conn udp_conn_clean
.PHONY: ipc_conn_clean
.PHONY: t09_tcp_clean


t01_num_endianess_convert: t01_num_endianess_convert.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

t02_inet_endian_convert: t02_inet_endian_convert.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@




single_conn_executables:=t03_single_conn_server t03_single_conn_client

t03_single_conn_server: t03_single_conn_server.c
	-$(CC) -o $@ $^

t03_single_conn_client: t03_single_conn_client.c
	-$(CC) -o $@ $^

single_conn: $(single_conn_executables)

single_conn_clean:
	-rm ./$(word 1, $(single_conn_executables)) ./$(word 2, $(single_conn_executables))


t04_without_buf_test: t04_without_buf_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


multi_conn_executables:=t05_multi_conn_threads_server t05_multi_conn_threads_client

t05_multi_conn_threads_server: t05_multi_conn_threads_server.c
	-$(CC) -o $@ $^

t05_multi_conn_threads_client: t05_multi_conn_threads_client.c
	-$(CC) -o $@ $^

multi_conn: $(multi_conn_executables)

multi_conn_clean:
	-rm ./$(word 1, $(multi_conn_executables)) ./$(word 2, $(multi_conn_executables))



multi_conn_pro_executables:=t06_multi_conn_processes_server t06_multi_conn_processes_client

t06_multi_conn_processes_server: t06_multi_conn_processes_server.c
	-$(CC) -o $@ $^

t06_multi_conn_processes_client: t06_multi_conn_processes_client.c
	-$(CC) -o $@ $^

multi_conn_pro: $(multi_conn_pro_executables)

multi_conn_pro_clean:
	-rm ./$(word 1, $(multi_conn_pro_executables)) ./$(word 2, $(multi_conn_pro_executables))



   

udp_conn_executables:=t07_udp_server t07_udp_client

t07_udp_server: t07_udp_server.c
	-$(CC) -o $@ $^

t07_udp_client: t07_udp_client.c
	-$(CC) -o $@ $^

udp_conn: $(udp_conn_executables)


udp_conn_clean:
	-rm ./$(word 1, $(udp_conn_executables)) ./$(word 2, $(udp_conn_executables))



t08_socket_ipc_test: t08_socket_ipc_test.c
	-$(CC) -o $@ $^
ipc_conn_clean: 
	-rm ./t08_socket_ipc_test




tcp_executables:=t09_tcp_server t09_tcp_client

t09_tcp_server: t09_tcp_server.c
	-$(CC) -o $@ $^

t09_tcp_client: t09_tcp_client.c
	$(CC) -o $@ $^

t09_tcp_clean:
	-rm ./$(word 1, $(tcp_executables)) ./$(word 2, $(tcp_executables))

t09_daemon_test: t09_daemon_test.c t09_tcp_clean t09_tcp_server t09_tcp_client
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@

t10_epoll_test: t10_epoll_test.c 
	$(CC) -o $@ $^
	-./$@
	-rm ./$@