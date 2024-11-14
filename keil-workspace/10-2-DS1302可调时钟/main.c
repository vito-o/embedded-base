#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

unsigned char keyNum, mode, timeSetSelect, timeSetFlashFlag;

void timeShow()
{
		DS1302_readTime();
		
		LCD_ShowNum(1, 1, DS1302_Time[0], 2);
		LCD_ShowNum(1, 4, DS1302_Time[1], 2);
		LCD_ShowNum(1, 7, DS1302_Time[2], 2);
		LCD_ShowNum(2, 1, DS1302_Time[3], 2);
		LCD_ShowNum(2, 4, DS1302_Time[4], 2);
		LCD_ShowNum(2, 7, DS1302_Time[5], 2);
}

void timeSet()
{
	if (keyNum == 2) // 按键2 按下
	{
		timeSetSelect++; 		// 设置选择位+1
		timeSetSelect %= 6;	// 处理越界
	}
	
	if (keyNum == 3) // 按键3 按下
	{
		DS1302_Time[timeSetSelect]++; //时间设置位数+1
		
		//判断越界
		//年
		if (DS1302_Time[0] > 99) DS1302_Time[0] = 0;
		//月
		if (DS1302_Time[1] > 12) DS1302_Time[1] = 1;
		//日
		if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)
		{ //大月
			if (DS1302_Time[2] > 31) DS1302_Time[2] = 1;
		}
		if (DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 || DS1302_Time[1] == 11)
		{	//小月
			if (DS1302_Time[2] > 30) DS1302_Time[2] = 1;
		}
		if (DS1302_Time[1] == 2)
		{	//二月
			if (DS1302_Time[0]%4==0) { // 闰年
				if (DS1302_Time[2] > 29) DS1302_Time[2] = 1;
			}
			else {
				if (DS1302_Time[2] > 28) DS1302_Time[2] = 1;
			}
		}
		// 时
		if (DS1302_Time[3] > 23) DS1302_Time[3] = 0;
		// 分
		if (DS1302_Time[4] > 59) DS1302_Time[4] = 0;
		// 秒
		if (DS1302_Time[5] > 59) DS1302_Time[5] = 0;
	}
	
	if (keyNum == 4) // 按键4 按下
	{
		DS1302_Time[timeSetSelect]--; //时间设置位数+1
		//判断越界
		//年
		if (DS1302_Time[0] < 0) DS1302_Time[0] = 99;
		//月
		if (DS1302_Time[1] < 1) DS1302_Time[1] = 12;
		//日
		if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)
		{ //大月
			if (DS1302_Time[2] < 1)  DS1302_Time[2] = 31;
			if (DS1302_Time[2] > 31) DS1302_Time[2] = 1;
		}
		if (DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 || DS1302_Time[1] == 11)
		{	//小月
			if (DS1302_Time[2] < 1)  DS1302_Time[2] = 30;
			if (DS1302_Time[2] > 30) DS1302_Time[2] = 1;
		}
		if (DS1302_Time[1] == 2)
		{	//二月
			if (DS1302_Time[0]%4==0) { // 闰年
				if (DS1302_Time[2] < 1)  DS1302_Time[2] = 29;
				if (DS1302_Time[2] > 29) DS1302_Time[2] = 1;
			}
			else {
				if (DS1302_Time[2] < 1 ) DS1302_Time[2] = 28;
				if (DS1302_Time[2] > 28) DS1302_Time[2] = 1;
			}
		}
		// 时
		if (DS1302_Time[3] < 0) DS1302_Time[3] = 23;
		// 分
		if (DS1302_Time[4] < 0) DS1302_Time[4] = 59;
		// 秒
		if (DS1302_Time[5] < 0) DS1302_Time[5] = 59;
	}
	
	//更新显示，根据TimeSetSelect和TimeSetFlashFlag判断可完成闪烁功能
	//timeSetSelect, timeSetFlashFlag
	if (timeSetSelect==0 && timeSetFlashFlag==1) LCD_ShowString(1, 1, "  ");
	else LCD_ShowNum(1, 1, DS1302_Time[0], 2);
	if (timeSetSelect==1 && timeSetFlashFlag==1) LCD_ShowString(1, 4, "  ");
	else LCD_ShowNum(1, 4, DS1302_Time[1], 2);
	if (timeSetSelect==2 && timeSetFlashFlag==1) LCD_ShowString(1, 7, "  ");
	else LCD_ShowNum(1, 7, DS1302_Time[2], 2);
	if (timeSetSelect==3 && timeSetFlashFlag==1) LCD_ShowString(2, 1, "  ");
	else LCD_ShowNum(2, 1, DS1302_Time[3], 2);
	if (timeSetSelect==4 && timeSetFlashFlag==1) LCD_ShowString(2, 4, "  ");
	else LCD_ShowNum(2, 4, DS1302_Time[4], 2);
	if (timeSetSelect==5 && timeSetFlashFlag==1) LCD_ShowString(2, 7, "  ");
	else LCD_ShowNum(2, 7, DS1302_Time[5], 2);
	
}

void main(){
	
	LCD_Init();
	DS1302_Init();
	Timer0Init();
	
	LCD_ShowString(1, 1, "  -  -  ");
	LCD_ShowString(2, 1, "  :  :  ");
	//如果读出时间为一个大于59并且不动的数，则芯片可能是处于写保护状态，在此处加上这行代码即可解除芯片写保护
	//DS1302_WriteByte(0x8E, 0x00);
	
	DS1302_setTime();
	
	while(1) {
		
		keyNum = Key();
		if (keyNum == 1) // 按键1 按下
		{
			// 功能切换
			if (mode == 0) {
				mode = 1;
				timeSetSelect = 0;
			}
			else if(mode == 1) {
				mode = 0;
				DS1302_setTime();
			}
		}
		
		switch(mode)
		{
			case 0: timeShow();break;
			case 1: timeSet();break;
		}
		
	}
}


void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		timeSetFlashFlag = !timeSetFlashFlag;
	}
}