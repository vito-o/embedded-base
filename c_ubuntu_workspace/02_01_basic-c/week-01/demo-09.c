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
	//	TEST();		//编译会报错，宏定义会原样替换，这里就会变为p_demo_01();p_demo_02();，因为if没有{}括号，所以只能执行一句， 所以习惯用do..while(0)替换
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