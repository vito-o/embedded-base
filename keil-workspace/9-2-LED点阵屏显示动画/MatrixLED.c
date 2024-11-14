#include <REGX52.H>
#include "Delay.h"

#define MATRIX_LED_PORT P0

sbit _SRCLK = P3^6;	// 移位寄存器时钟输入
sbit _RCLK  = P3^5;	// 存储寄存器时钟输入
sbit _SER   = P3^4; // 串行输入数据

void MatrixLED_init()
{
	_SRCLK = 0;
	_RCLK = 0;
}

void _74HC595_WriteByte(unsigned char byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++) {
		_SER = byte & (0x80 >> i);
		_SRCLK = 1;
		_SRCLK = 0;
	}
	_RCLK = 1;
	_RCLK = 0;
}


// 先列后行扫描
void MatrixLED_ShowColIndex(unsigned char colIndex, unsigned char byte)
{
	_74HC595_WriteByte(byte);
	
	MATRIX_LED_PORT = ~(0x80 >> colIndex);
	// 消影
	Delay(1);
	MATRIX_LED_PORT = 0xFF;
}