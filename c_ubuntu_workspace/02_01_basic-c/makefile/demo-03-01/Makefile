SUB_DIR := main fun global obj

# 设置SUB_DIR变量导出为全局，其他文件也可以使用
export SUB_DIR

all: $(SUB_DIR)

$(SUB_DIR): MK_BIN
	make -C $@

MK_BIN: 
	mkdir -p ./bin

clean:
	rm -rf *.bin ./obj/*.o