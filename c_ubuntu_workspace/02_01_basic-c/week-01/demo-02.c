#include <stdio.h>

void do_local()
{
	//static ֻ��main����ִ�н�����Ż��գ� Ĭ��Ϊ0
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