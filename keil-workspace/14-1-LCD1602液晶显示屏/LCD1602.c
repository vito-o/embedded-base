#include <REGX52.H>

//引脚定义
sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;

#define LCD_DataPort P0

/**
  * @brief  LCD1602延时函数，12MHz调用可延时1ms
  * @param  无
  * @retval 无
  */
void LCD_Delay()		//@12.000MHz 1ms
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

int LCD_Pow(int x, int y)
{
	unsigned char i;
	int res = 1;
	for(i = 0; i < y; i++)
	{
		res *= x;
	}
	return res;
}

void LCD_WriteCommand(unsigned char command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = command;
	
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 1;
	LCD_Delay();
}

void LCD_WriteData(unsigned char byte)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = byte;
	
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 1;
	LCD_Delay();
}

void LCD_Init()
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0c);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}

void LCD_Cursor(unsigned char line, unsigned char col)
{
	if (line == 1) {
		LCD_WriteCommand(0x80|(col-1));
	} else {
		LCD_WriteCommand(0x80|(col-1)+0x40);
	}
}

void LCD_ShowChar(unsigned char line, unsigned char col, unsigned char ch)
{
	LCD_Cursor(line, col);
	LCD_WriteData(ch);
}

void LCD_ShowString(unsigned char line, unsigned char col, unsigned char *string)
{
	unsigned char i;
	
	LCD_Cursor(line, col);
	for (i = 0; string[i] != '\0'; i++) {
		LCD_WriteData(string[i]);
	}
}

void LCD_ShowNum(unsigned char line, unsigned char col, unsigned int num, unsigned char len)
{
	unsigned char i;
	
	LCD_Cursor(line, col);
	for (i = len; i > 0; i--) {
		LCD_WriteData(num/LCD_Pow(10, i-1)%10 + '0');
	}
}

void LCD_ShowSignNum(unsigned char line, unsigned char col, unsigned int num, unsigned char len)
{
	unsigned char i;
	unsigned int temp;
	
	LCD_Cursor(line, col);
	
	if (num >= 0) 
	{
		LCD_WriteData('+');
		temp = num;
	}
	else
	{
		LCD_WriteData('-');
		temp = -num;
	}
	
	for (i = len; i > 0; i--) {
		LCD_WriteData(temp/LCD_Pow(10, i-1)%10 + '0');
	}
}

void LCD_ShowHexNum(unsigned char line, unsigned char col, unsigned int num, unsigned char len)
{
	unsigned char i;
	unsigned signNum;
	
	LCD_Cursor(line, col);
	
	for (i = len; i > 0; i--) {
		signNum = num/LCD_Pow(16, i-1)%16;
		if (signNum < 10)
		{
			LCD_WriteData(signNum + '0');
		}
		else
		{
			LCD_WriteData(signNum-10 + 'A');
		}	
	}
}

void LCD_ShowBinNum(unsigned char line, unsigned char col, unsigned int num, unsigned char len)
{
	unsigned char i;
	
	LCD_Cursor(line, col);
	for (i = len; i > 0; i--) {
		LCD_WriteData(num/LCD_Pow(2, i-1)%2 + '0');
	}
}