#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int add_07(const int a, const int b)
{
	return a + b;
}

int sub_07(const int a, const int b)
{
	return a - b;
}

//�������ʹ������ĵ�ַ
//const int a = 20
//const int b = 10
//int (*funp)(const int a, const int b) = add
// ��
//int (*funp)(const int a, const int b) = add
int calc(const int a, const int b, int (*funp)(const int, const int))
{
	int ret = 0;
	ret = funp(a, b);
	return ret;
}


//����ָ�� 02  �ص�����
int main_07()
{
	int ret = 0;

	ret = calc(20, 10, add_07);
	printf("a + b = %d\n", ret);
	
	ret = calc(20, 10, sub_07);
	printf("a - b = %d\n", ret);

	return 0;
}