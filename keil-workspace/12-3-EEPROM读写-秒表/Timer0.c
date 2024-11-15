#include <REGX52.H>

void Timer0_Init(void)
{	
	//设置定时器模式，
	// 在前4位不变的情况下，改变后四位	
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	TF0 = 0;
	TR0 = 1;
	
	//1us
	TH0 = 64535/256;
	TL0 = 64535%256;
	
	// 开启中断
	ET0 = 1;
	EA  = 1;
}

/*
// 中断示例
void Timer0_Routine() interrupt 1
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