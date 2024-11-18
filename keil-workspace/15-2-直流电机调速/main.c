#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

// PWM
sbit LED = P2^0;
sbit Moter = P1^0;

unsigned char keyNum, speed;
unsigned char counter, compare;

void main() 
{
	Timer0_Init();
	
	while(1)
	{
			keyNum = Key();
		
			if (keyNum == 1)
			{
				speed++;
				speed%=4;
				if(speed == 0) compare = 0;
				if(speed == 1) compare = 20;
				if(speed == 2) compare = 55;
				if(speed == 3) compare = 100;
			}
			
			Nixie(1, speed);
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
		Moter = 1;
	}
	else
	{
		LED = 1;
		Moter = 0;
	}
}