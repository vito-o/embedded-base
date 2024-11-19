#include <REGX52.H>

//INT0 == P3^2 触发外部中断
void Int0_init(void)
{

	IT0 = 1;
	IE0 = 0; //外部中断0向cpu请求中断
	
	EX0 = 1;
	EA  = 1;
	
	//如果只设置IP，那么中断优先级只有两级， px0 在 IP中
	//IPH &= 0xF0;
	//IPH |= 0x01;
	//PX0H = 1;
	PX0 = 1;
	
}

/*

void Int0_Routine(void) interrupt 0;

*/