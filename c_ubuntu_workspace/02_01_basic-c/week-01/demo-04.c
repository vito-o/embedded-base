#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>


int main_04()
{
	char buf[100];

	printf("please input string: ");

	scanf("%s", buf);

	//计算用户实际输入的元素个数
	printf("strlen(buf) = %d\n", strlen(buf));
	//计算数据所在内存空间的大小
	printf("sizeof(buf) = %ld\n", sizeof(buf));

	return 0;
}