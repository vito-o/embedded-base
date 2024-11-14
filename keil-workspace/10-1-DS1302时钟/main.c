#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"

unsigned char second;

void main(){

	LCD_Init();
	DS1302_Init();
	
	LCD_ShowString(1, 1, "  -  -  ");
	LCD_ShowString(2, 1, "  :  :  ");
	//如果读出时间为一个大于59并且不动的数，则芯片可能是处于写保护状态，在此处加上这行代码即可解除芯片写保护
	//DS1302_WriteByte(0x8E, 0x00);
	
	DS1302_setTime();
	
	while(1) {
		DS1302_readTime();
		
		LCD_ShowNum(1, 1, DS1302_Time[0], 2);
		LCD_ShowNum(1, 4, DS1302_Time[1], 2);
		LCD_ShowNum(1, 7, DS1302_Time[2], 2);
		LCD_ShowNum(2, 1, DS1302_Time[3], 2);
		LCD_ShowNum(2, 4, DS1302_Time[4], 2);
		LCD_ShowNum(2, 7, DS1302_Time[5], 2);
	}
	
}