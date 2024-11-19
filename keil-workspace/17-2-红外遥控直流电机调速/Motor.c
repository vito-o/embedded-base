#include <REGX52.H>
#include "Delay.h"
#include "Timer1.h"

// PWM
sbit LED = P2^0;
sbit Moter = P1^0;

unsigned char counter,compare;

void Motor_Init(void)
{
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char Speed)
{
	compare = Speed;
}


void Timer0_Routine() interrupt 3
{
	TH0 = 0xFF;
	TL0 = 0x9C;
	
	counter++;
	counter%=100;
	
	if (counter < compare) 
	{
		LED = 0;
		Moter = 1;
	}
	else
	{
		LED = 1;
		Moter = 0;
	}
}



