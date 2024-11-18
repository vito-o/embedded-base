#include "Dir_1Wrie.h"
#include "Delay.h"
#include <REGX52.H>

float Int_DS18B20_GetTemperature()
{
	int Temp;
	unsigned char ls_byte;
	unsigned char ms_byte;
	
	//初始化
	Dir_1Wire_Init();
	//发送ROM命令
	Dir_1Wire_WriteByte(0xCC);
	//发送测温命令
	Dir_1Wire_WriteByte(0x44);
	
	Delay(1000);
	
	//初始化
	Dir_1Wire_Init();
	//发送ROM命令
	Dir_1Wire_WriteByte(0xCC);
	//发送读取命令
	Dir_1Wire_WriteByte(0xBE);
	
	ls_byte = Dir_1Wire_ReadByte();
	ms_byte = Dir_1Wire_ReadByte();
	
//	return (ls_byte >> 4) | (ms_byte << 4);
	Temp = (ms_byte << 8) | ls_byte; 
	return Temp/16.0;
}
