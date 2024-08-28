#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int add(const int a, const int b)
{
	return a + b;
}

int sub(const int a, const int b)
{
	return a - b;
}

//函数指针
//本质是一个指针，只不过用来保存函数的地址的
//通过函数指针来调用我们需要的函数
int main_06()
{
	int ret = 0;

	ret = add(10, 20);		//ret = 0x5655751d(10, 20)
	printf("a + b = %d\n", ret);

	printf("add = %p\n", add);
	printf("-----------------------\n");

	int(*funp)(int, int) = add; // funp == add == 0x5655751d

	ret = funp(10, 20);
	printf("a + b = %d\n", ret);

	return 0;
} 