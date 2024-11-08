#include <REGX52.H>

void main() 
{
	//启用中断
	EX0 = 1;
	EA = 1;
	
	//触发方式（下降沿）
	IT0 = 1;
	
	while(1)
	{
		if (P3_1 == 0)
		{
			P3_2 = 0;
		}
		else
		{
			P3_2 = 1;
		}
	}
}

void Int0_Routine(void) interrupt 0
{
	P2_0 = ~P2_0;
}