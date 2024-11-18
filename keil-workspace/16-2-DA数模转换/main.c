#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"

// PWM
sbit LED = P2^0;
sbit DA = P2^1;

unsigned char counter, compare;
unsigned char i;

void main() 
{
	Timer0_Init();
	
	while(1)
	{
		for(i=0;i<100;i++)
		{
			compare=i;			//设置比较值，改变PWM占空比
			Delay(10);
		}
		for(i=100;i>0;i--)
		{
			compare=i;			//设置比较值，改变PWM占空比
			Delay(10);
		}
	}
}

void Timer0_Routine() interrupt 1
{
	TH0 = 0xFF;
	TL0 = 0x9C;
	
	counter++;
	counter%=100;
	
	if (counter < compare) 
	{
		LED = 0;
		DA = 1;
	}
	else
	{
		LED = 1;
		DA = 0;
	}
}