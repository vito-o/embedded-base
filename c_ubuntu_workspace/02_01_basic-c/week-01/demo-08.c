#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

#define M 10
#define CALC(x) (x * x)
//����ԭ���滻

int main_08()
{
	printf("M = %d\n", M);	//10
	printf("Result = %d\n", CALC(M + M)); //120 ?

	// x = M + M
	// calc(x) (x * x) ==>  (M + M * M + M)
	// ===> 10 + 10 * 10 + 10 = 120
	//ubuntu  cmd   
	//gcc -E demo-08.c -o demo-08.i
	//vi demo-08.i
	//���Կ���������
	return 0;
}