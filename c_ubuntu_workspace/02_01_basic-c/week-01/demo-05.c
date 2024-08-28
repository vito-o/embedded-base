#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int* design_array(int* plen)
{
	static int a[] = { 100, 200, 300, 400, 500 };
	int len = sizeof(a) / sizeof(a[0]);
	*plen = len;
	return a;
}

void output_array1(int* p, int plen)
{
	int i = 0;
	for (i = 0; i < plen; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
}

//指针函数,  返回值是一个地址
int main_05()
{
	int* p = NULL;
	int num = 0, i = 0;

	p = design_array(&num);

	output_array1(p, num);
	return 0;
}