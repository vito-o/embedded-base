#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "IR.h"

unsigned char address;
unsigned char command;
unsigned char count;

void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "ADDR  CMD  NUM");
	LCD_ShowString(2, 1, "00    00   000");

	IR_init();
	
	while(1)
	{
		if (IR_getDataFlag())
		{
			address = IR_getAddress();
			LCD_ShowNum(2, 1, address, 2);
			
			command = IR_getCommand();
			LCD_ShowNum(2, 7, command, 2);
			
			if (command == IR_VOL_MINUS)
			{
				count--;
			}
			if (command == IR_VOL_ADD)
			{
				count++;
			}
			LCD_ShowNum(2, 12, count, 3);
		}
	}
}

