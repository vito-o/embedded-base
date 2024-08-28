.PHONY: named_fifo named_fifo_clean

CC:=gcc


# system_test: system_test.c
# 	-${CC} -o $@ $^
# 	-./$@
# 	-rm ./$@


fork_test: fork_test.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@


fork_fd_test: fork_fd_test.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@



erlou: erlou.c
	-${CC} -o $@ $^
	

# execve_test: execve_test.c
# 	-${CC} -o $@ $^
# 	-./$@
# 	-rm ./$@

execve_test: execve_test.c erlou
# $< 取依赖列表的第一个文件，此处是execve_test.c。 等价于$(firstword $^)
# $(word 2, $^) 取依赖列表的第二个文件，此处等价于erlou,
# 这里也可以用${lastword $^}表示取依赖列表的最后一个文件，也就是erlou
	-${CC} -o $@ $<
	-./$@
	-rm ./$@ ./${word 2, $^}


fork_execve_test: fork_execve_test.c erlou
	-${CC} -o $@ $<
	-./$@
	-rm ./$@ ./${word 2, $^}


waitpid_test: waitpid_test.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@


pstree_test: pstree_test.c erlou
	-${CC} -o $@ $<
	-./$@
	-rm ./$@ ./${word 2, $^}


erlou_block: erlou_block.c
	-${CC} -o $@ $^

orphan_process_test: orphan_process_test.c erlou_block
	-${CC} -o $@ $<
	-./$@
	-rm ./$@ ./${word 2, $^}


perror_test: perror_test.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@

errno_test: errno_test.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@

process_test: process_test.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@

unnamed_pipe_test: unnamed_pipe_test.c
	-${CC} -o $@ $^
	-./$@ hello
	-rm ./$@


fifo_write: fifo_write.c
	-${CC} -o $@ $^

fifo_read: fifo_read.c
	-${CC} -o $@ $^

named_fifo: fifo_write fifo_read

named_fifo_clean:
	-rm ./fifo_write ./fifo_read


shared_memory: shared_memory.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@

shared_memory_block: shared_memory_block.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@

father_son_mq_test: father_son_mq_test.c
	-${CC} -o $@ $^
	-./$@
	-rm ./$@


mq_producer: mq_producer.c
	-${CC} -o $@ $^

mq_consumer: mq_consumer.c
	-${CC} -o $@ $^

named_mq: mq_producer mq_consumer

named_mq_clean:
	-rm ./mq_producer ./mq_consumer