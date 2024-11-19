#include <REGX52.H>

void Timer1_Init(void)
{	
	//设置定时器模式，
	// 在前4位不变的情况下，改变后四位	
	TMOD &= 0x0F;
	TMOD |= 0x10;
	
	TF1 = 0;
	TR1 = 1;
	
	//1us
	TH1 = 0xFF;
	TL1 = 0x9C;
	
	// 开启中断
	ET1 = 1;
	EA  = 1;
	
	PT1 = 0;
}

/*
// 中断示例
void Timer0_Routine() interrupt 3
{
	static unsigned int T0Count;
	
	TH0 = 64535/256;
	TL0 = 64535%256;
	T0Count++;
	if (T0Count >= 1000)
	{
		T0Count = 0;
		P2_0 = ~P2_0;
	}
}

*/