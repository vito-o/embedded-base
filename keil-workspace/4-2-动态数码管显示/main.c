#include <REGX52.H>
/*
单片机直接扫描:
硬件设备简单，但会消耗大量的单片机cpu时间
（当前程序用的这个)

也可以用
专用驱动芯片:
	内部自带显存、扫描电路，单片机只需告诉它显示生命即可
	TM1640
*/
void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		
		xms--;
	}
	
}

unsigned char NixieTable[] =  {
	0x3F, 0x06, 0x5B, 0x4F,
	0x66, 0x6D, 0x7D, 0x07,
	0x7F, 0x6F
};

void Nixie(unsigned char location, num)
{
	switch(location)
	{
		case 1: P2_4=1;P2_3=1;P2_2=1;break;
		case 2: P2_4=1;P2_3=1;P2_2=0;break;
		case 3: P2_4=1;P2_3=0;P2_2=1;break;
		case 4: P2_4=1;P2_3=0;P2_2=0;break;
		case 5: P2_4=0;P2_3=1;P2_2=1;break;
		case 6: P2_4=0;P2_3=1;P2_2=0;break;
		case 7: P2_4=0;P2_3=0;P2_2=1;break;
		case 8: P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[num];
	
	// 消影
	Delay(1);
	P0 = 0x00;
}

void main () 
{
	while(1) {
		Nixie(1,1);
		//Delay(200);
		Nixie(2,2);
		//Delay(200);
		Nixie(3,3);
		//Delay(200);
	}
}