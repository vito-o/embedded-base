#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>


int main_04()
{
	char buf[100];

	printf("please input string: ");

	scanf("%s", buf);

	//�����û�ʵ�������Ԫ�ظ���
	printf("strlen(buf) = %d\n", strlen(buf));
	//�������������ڴ�ռ�Ĵ�С
	printf("sizeof(buf) = %ld\n", sizeof(buf));

	return 0;
}