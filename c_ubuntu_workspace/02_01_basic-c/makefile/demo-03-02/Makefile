CC := gcc
INCLUDE_DIR := -I ../include
OBJ_DIR := $(shell pwd)/obj
BIN_DIR := $(shell pwd)/bin

SUB_DIR := main fun global obj

TARGET := my_exec

# 设置SUB_DIR变量导出为全局，其他文件也可以使用
export CC INCLUDE_DIR OBJ_DIR BIN_DIR SUB_DIR TARGET

all: $(SUB_DIR)

$(SUB_DIR): MK_BIN
	make -C $@

MK_BIN: 
	mkdir -p ./bin

clean:
	rm -rf *.bin ./obj/*.o

install:
	sudo cp $(BIN_DIR)/$(TARGET) /usr/bin

uninstall:
	sudo rm -rf /usr/bin/$(TARGET)