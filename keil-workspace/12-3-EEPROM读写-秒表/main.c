#include <REGX52.H>
#include "Int_EEPROM.h"
#include "Key.h"
#include "Delay.h"
#include "Nixie.h"
#include "Timer0.h"

unsigned char keyNum;
unsigned char min, sec, miniSec;
unsigned char runFlag;

unsigned char time[3];

void main() 
{
	Timer0_Init();
	
	while(1) {
		keyNum = Key();
		
		if (keyNum == 1) 
		{
			runFlag = !runFlag; //启动/暂停
		}
		
		else if (keyNum == 2) // 重置清零
		{
			min = 0;
			sec = 0;
			miniSec = 0;
		}
		
		else if (keyNum == 3)	// 将数据存储到EEPROM中
		{
			time[0] = min;
			time[1] = sec;
			time[2] = miniSec;
			
			Int_EEPROM_WriteBytes(0, time, 3);
			// 存储后缓存清空
			time[0] = 0;
			time[1] = 0;
			time[2] = 0;
		}
		
		else if (keyNum == 4)	// 将数据从EEPROM中读出，在数码管显示
		{
			Int_EEPROM_ReadBytes(0, time, 3);
			min = time[0];
			sec = time[1];
			miniSec = time[2];
		}
		
		// 显示
		Nixie(1, min/10);
		Nixie(2, min%10);
		
		Nixie(3, 11);
		
		Nixie(4, sec/10);
		Nixie(5, sec%10);
		
		Nixie(6, 11);
		
		Nixie(7, miniSec/10);
		Nixie(8, miniSec%10);
	}
}

void sec_loop()
{
	if (runFlag)
	{
		miniSec++;
		if (miniSec >= 100)
		{
			miniSec = 0;
			sec++;
			if (sec >= 60) 
			{
				sec = 0;
				min++;
				
				if(min >= 60) {
					min = 0;
				}
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count1, T0Count2, T0Count3;
	
	TH0 = 64535/256;
	TL0 = 64535%256;
	T0Count1++;
	if (T0Count1 >= 20) //20ms调用一次按键驱动函数
	{
		T0Count1 = 0;
		sec_loop();
	}
	
	T0Count2++;
	if (T0Count2 >= 20) //20ms调用一次按键驱动函数
	{
		T0Count2 = 0;
		sec_loop();
	}
	
	T0Count3++;
	if (T0Count3 >= 20) //20ms调用一次按键驱动函数
	{
		T0Count3 = 0;
		sec_loop();
	}
}
