#include <stdio.h>

//×Ö·û´®»¯ÔËËã·û

#define Fun(x) printf(#x " = %d\n", x)

#define STR(x) #x
#define NUM 10

int main_10()
{
	Fun(4 + 2);					// 4 + 2 = 6

	printf("%s\n", STR(3));		// 3
	printf("%s\n", STR(NUM));	// NUM
}