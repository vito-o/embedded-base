#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

void p_demo_01()
{
	printf("p_demo_01\n");
}
void p_demo_02()
{
	printf("p_demo_02\n");
}
void p_demo_03()
{
	printf("p_demo_03\n");
}

#define TEST() p_demo_01();p_demo_02();

#define TEST1() do {	\
	p_demo_01();		\
	p_demo_02();		\
} while(0)				 

int main_09()
{
	//int i = 1;
	//if (i == 1)
	//	TEST();		//����ᱨ���궨���ԭ���滻������ͻ��Ϊp_demo_01();p_demo_02();����Ϊifû��{}���ţ�����ֻ��ִ��һ�䣬 ����ϰ����do..while(0)�滻
	//else
	//	p_demo_03();
	//----------------------------------
	int i = 1;
	if (i == 1)
		TEST1();
	else
		p_demo_03();

	return 0;
}