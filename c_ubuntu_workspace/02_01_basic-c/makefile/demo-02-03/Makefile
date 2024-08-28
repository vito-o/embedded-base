# 伪目标， 防止目标名称和 文件名称重复导致，makefile命令无法执行
.PHONY : clean

CC := gcc

# $@: 目标的集合
# $<: 第一个依赖条件
# $^: 所有的依赖条件

TARGET := main_exec
# OBJECT := main.o fun.o

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $@

%.o : %.c
	$(CC) -c $< -o $@

clean:
	rm -rf *.o main_exec