# -c：表示只编译源文件但不链接，只会把.c源程序编译成目标文件，一般是.o文件
# -o：表示指定输出文件名。不用-o的话，一般会在当前文件夹下生成默认的a.out作为可执行程序
# 例如
# gcc -c test.c将生成test.o的目标文件
# gcc -o app test.c生成可执行程序app

main.o: main.c
	gcc -c main.c -o main.o

fun.o: fun.c
	gcc -c fun.c -o fun.o

main_exec: main.o fun.o
	gcc main.o fun.o -o main_exec

clean:
	rm -rf *.o main_exec