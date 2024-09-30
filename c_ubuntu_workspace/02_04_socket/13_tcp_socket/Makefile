TARGET:= server client
OBJ1 := server.o tcpsocket.o
OBJ2 := client.o tcpsocket.o

all: $(TARGET)

server: $(OBJ1)
	@gcc $^ -o $@
	@echo "Done server."

client: $(OBJ2)
	@gcc $^ -o $@
	@echo "Done client."

%.o: %.c
	@gcc -c $< -o $@

clean:
	@rm *.o server client
	@echo "Clean."

