# -c：表示只编译源文件但不链接，只会把.c源程序编译成目标文件，一般是.o文件
# -o：表示指定输出文件名。不用-o的话，一般会在当前文件夹下生成默认的a.out作为可执行程序
# 例如
# gcc -c test.c将生成test.o的目标文件
# gcc -o app test.c生成可执行程序app

# $@: 目标的集合
# $<: 第一个依赖条件
# $^: 所有的依赖条件

# 目标：会在上级的obj目录产生fun.o文件
# ../obj/fun.o

# 前置依赖
# fun.c

# 指定头文件在哪里
# -I ../include/
../obj/fun.o : fun.c
	gcc -I ../include/ -c $< -o $@