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

//����ָ��
//������һ��ָ�룬ֻ�����������溯���ĵ�ַ��
//ͨ������ָ��������������Ҫ�ĺ���
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