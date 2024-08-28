# 获取当前目录下的所有.c文件
SRC=$(wildcard *.c)

# 准备把当前目录下的.c转换为.o文件 
OBJ=$(patsubst %c, %o, $(SRC))

all: $(OBJ)

$(OBJ): %.o:%.c
	$(CC) $(INCLUDE_DIR) -c $^ -o $(OBJ_DIR)/$@

