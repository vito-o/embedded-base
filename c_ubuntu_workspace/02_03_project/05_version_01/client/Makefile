OBJS:=sem.o shmfifo.o shm.o client.o main.o msg.o

client: $(OBJS)
	@gcc $^ -o $@ -lpthread
	@echo "Done."

%.o : %.c
	@gcc -c $< -o $@

clean:
	@rm *.o client
	@echo "CLean."