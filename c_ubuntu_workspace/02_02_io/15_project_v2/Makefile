# 所有依赖的目标文件
OBJS := main.o cmd_ls.o cmd_cp.o cmd_handle.o 
# 目标文件
TARGET := tinyshell

$(TARGET): $(OBJS)
	@gcc $^ -o $@  		# $^:依赖的所有文件  $@: 目标文件
	@echo "Done."

# 自动推导
%.o: %.c
	@gcc -c $< -o $@	# $<:依赖的第一个文件 $@: 目标文件

# 清除目标
clean:
	rm -rf *.o $(TARGET)	# 删除相关依赖文件