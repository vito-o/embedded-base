#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int val;

void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "ADJ  NTC  GR");
	//XPT2046_ReadAD();
	while(1)
	{
		val = XPT2046_ReadAD(XPT2046_XP);		//读取AIN0，可调电阻
		LCD_ShowNum(2, 1, val, 3);
		
		val = XPT2046_ReadAD(XPT2046_YP);		//读取AIN1，热敏电阻
		LCD_ShowNum(2, 6, val, 3);
		
		val = XPT2046_ReadAD(XPT2046_VBAT);	//读取AIN2，光敏电阻
		LCD_ShowNum(2, 11, val, 3);
		
		Delay(100);
	}
	
	
}