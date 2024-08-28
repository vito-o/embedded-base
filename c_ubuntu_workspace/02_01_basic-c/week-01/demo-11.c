#include <stdio.h>

//×Ö·û´®»¯ÔËËã·û

#define LOG(...) printf(__VA_ARGS__)
#define LOGSTR(fm, ...) printf(fm, __VA_ARGS__)

int main()
{
	LOG("This Time is %d o'clock\n", 9);
	LOG("This Time is %d:%d:%d\n", 18,12,23);

	LOGSTR("data = %d %s\n", 100, "RMB");
}