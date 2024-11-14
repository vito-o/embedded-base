#include <REGX52.H>
#include "Delay.h"

sbit _SRCLK = P3^6;	// 移位寄存器时钟输入
sbit _RCLK  = P3^5;	// 存储寄存器时钟输入
sbit _SER   = P3^4; // 串行输入数据

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

#define MATRIX_LED_PORT P0

// 先列后行扫描
void MatrixLED_ShowColIndex(unsigned char colIndex, unsigned char byte)
{
	_SRCLK = 0;
	_RCLK = 0;
	_74HC595_WriteByte(byte);
	
	MATRIX_LED_PORT = ~(0x80 >> colIndex);
	// 消影
	Delay(1);
	MATRIX_LED_PORT = 0xFF;
}

void main()
{
		while(1)
		{
			MatrixLED_ShowColIndex(0, 0x3C);
			MatrixLED_ShowColIndex(1, 0x42);
			MatrixLED_ShowColIndex(2, 0xA9);
			MatrixLED_ShowColIndex(3, 0x85);
			MatrixLED_ShowColIndex(4, 0x85);
			MatrixLED_ShowColIndex(5, 0xA9);
			MatrixLED_ShowColIndex(6, 0x42);
			MatrixLED_ShowColIndex(7, 0x3C);
		}
}