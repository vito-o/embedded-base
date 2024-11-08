#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "MatrixKey.h"

unsigned char keyNum;
unsigned int password, count;

void main()	
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	count = 0;
	password = 0;
	
	while(1)
	{
		keyNum = MatrixKey();
		if (keyNum) {
			
			if (keyNum <= 10) {
				if (count < 4) {
					password =  password * 10;
					password += keyNum % 10;
					LCD_ShowNum(2,1,password,4);	
					count++;
				}				
			} else if (keyNum == 11) { // 确认
				if (password == 2345) {
					LCD_ShowString(1, 14, "OK ");
					LCD_ShowNum(2,1,password,4);
				} else {
					LCD_ShowString(1, 14, "ERR");
				}
				password = 0;
				count = 0;
			} else if (keyNum == 12) { // 取消
				password = 0;
				count = 0;
				LCD_ShowNum(2,1,password,4);
				LCD_ShowString(1, 14, "   ");
			}

		}
	}
}