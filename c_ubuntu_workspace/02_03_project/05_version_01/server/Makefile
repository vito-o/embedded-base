OBJS:=sem.o shmfifo.o shm.o server.o main.o thread_pool.o hashmap.o msg.o

server: $(OBJS)
	@gcc $^ -o $@ -lpthread
	@echo "Done."

%.o : %.c
	@gcc -c $< -o $@

clean:
	@rm *.o server
	@echo "clean."