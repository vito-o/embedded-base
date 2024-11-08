#include <REGX52.H>
#include "LCD1602.h"
#include "Timer0.h"
#include "Delay.h"

unsigned char hour = 23, min = 59, sec = 55;

void main()	
{
	LCD_Init();
	Timer0_Init();
	
	LCD_ShowString(1,1,"Clock");
	LCD_ShowString(2,1,"  :  :  ");
	
	while(1) 
	{
		LCD_ShowNum(2,1,hour,2);
		LCD_ShowNum(2,4,min,2);
		LCD_ShowNum(2,7,sec,2);
	}
	
}


void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	
	TH0 = 64535/256;
	TL0 = 64535%256;
	T0Count++;
	if (T0Count >= 1000)
	{
		T0Count = 0;
		
		sec++;
		if (sec >= 60) {
			sec = 0;
			min++;
			
			if (min >= 60) {
				min = 0;
				hour++;
				
				if (hour >= 24) {
					hour = 0;
				}
			}
		}
	}
}