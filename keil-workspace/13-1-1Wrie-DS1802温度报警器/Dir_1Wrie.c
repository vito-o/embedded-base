#include <REGX52.H>
#include "Delay.h"

sbit DQ = P3^7;

unsigned char Dir_1Wire_Init()
{
	unsigned char result;
	unsigned char i;
	EA=0;
	
	DQ = 1;
	
	
	DQ = 0;
	//延时500us
	i = 247;while (--i);		//Delay 500us
	DQ = 1;
	
	// 延时70us
	i = 32;while (--i);			//Delay 70us
	result = ~DQ;
	
	// 延时420us
	i = 247;while (--i);		//Delay 500us
	EA=1;
	return result;
}

void Dir_1Wire_WriteByte(unsigned char byte)
{
	unsigned char i;
	unsigned char j;
	for (i = 0; i < 8; i++) {
		EA=0;
		
		DQ = 0;
		j = 4;while (--j);			//Delay 10us
		DQ = byte & 0x01;
		byte >>= 1;
		// 延时50us
		j = 24;while (--j);			//Delay 50us
		DQ = 1;
		
		EA=1;
	}
}

unsigned char Dir_1Wire_ReadByte()
{
	unsigned char byte = 0x00;
	unsigned char j;
	
	unsigned char i;
	for (i = 0; i < 8; i++) {
		EA=0;
		
		DQ = 0;
		j = 2;while (--j);			//Delay 5us
		DQ = 1;
		j = 2;while (--j);			//Delay 5us
		
		byte >>=1;
		if (DQ == 1) {
			byte |= 0x80;
		}
		j = 24;while (--j);
		
		EA=1;
	}
	
	return byte;
}