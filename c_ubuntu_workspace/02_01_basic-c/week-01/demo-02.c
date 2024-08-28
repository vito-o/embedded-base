#include <stdio.h>

void do_local()
{
	//static 只在main函数执行结束后才回收， 默认为0
	static int t = 10;
	t++;
	printf("%d\n", t);
}

int main_02()
{
	do_local();
	do_local();
	do_local();

	return 0;
}