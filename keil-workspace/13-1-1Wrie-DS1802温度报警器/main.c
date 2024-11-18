#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Int_DS18B20.h"
#include "Timer0.h"

unsigned char keyNum;
char TLow = 5, THigh = 20;
float T,TShow;

void main()
{
	Timer0_Init();
	
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);
	
	while(1)
	{		
		keyNum=Key();
		
		T = Int_DS18B20_GetTemperature();
		
		if(T<0)				//如果温度小于0
		{
			LCD_ShowChar(1,3,'-');	//显示负号
			TShow=-T;		//将温度变为正数
		}
		else				//如果温度大于等于0
		{
			LCD_ShowChar(1,3,'+');	//显示正号
			TShow=T;
		}
		
		LCD_ShowNum(1,4,TShow,3);
		LCD_ShowChar(1,7,'.');		//显示小数点
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);
	}
	
	if (keyNum) {
		
		if (keyNum == 1) {
			THigh++;
			if(THigh>125){THigh=125;}
		}
		
		if (keyNum == 2) {
			THigh--;
			if(THigh<=TLow){THigh++;}
		}
		
		if (keyNum == 3) {
			TLow++;
			if(TLow>=THigh){TLow--;}
		}
		
		if (keyNum == 4) {
			THigh--;
			if(TLow<-55){TLow=-55;}
		}
		
		LCD_ShowSignedNum(2,4,THigh,3);	//显示阈值数据
		LCD_ShowSignedNum(2,12,TLow,3);
	
	}
	
	if(T>THigh)			//越界判断
	{
		LCD_ShowString(1,13,"OV:H");
	}
	else if(T<TLow)
	{
		LCD_ShowString(1,13,"OV:L");
	}
	else
	{
		LCD_ShowString(1,13,"    ");
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=20)
	{
		T0Count=0;
		Key_Loop();	//每20ms调用一次按键驱动函数
	}
}
