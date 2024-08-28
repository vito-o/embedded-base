#include <stdio.h>

void output_array(int *p, const int plen)
{
	int i = 0;
	for (i = 0; i < plen; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
}

int main_03() 
{
	int a[5] = { 0 };
	int len = sizeof(a) / sizeof(a[0]);

	output_array(a, len);

	return 0;
}