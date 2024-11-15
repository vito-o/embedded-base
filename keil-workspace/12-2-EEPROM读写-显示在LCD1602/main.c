#include <REGX52.H>
#include "Int_EEPROM.h"
#include "LCD1602.h"
#include "Key.h"
#include "Delay.h"

unsigned char keyNum;
unsigned int Num = 2;

unsigned char data1[2],data2[2];

void main() 
{
	LCD_Init();
	LCD_ShowNum(1,1,Num,5);
	
	while(1) {
		keyNum = Key();
		
		if (keyNum == 1) 
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);
		}
		
		else if (keyNum == 2)
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		
		else if (keyNum == 3)
		{
			data1[0] = Num%256;
			data1[1] = Num/256;
			Int_EEPROM_WriteBytes(0, data1, 2);

			LCD_ShowString(2, 1, "Write OK");
			Delay(1000);
			LCD_ShowString(2, 1, "        ");
		}
		
		else if (keyNum == 4)
		{
			Int_EEPROM_ReadBytes(0, data2, 2);
			
			Num = data2[0];
			Num |= data2[1] << 8;
			
			LCD_ShowNum(1,1,Num,5);
			
			LCD_ShowString(2, 1, "Read OK");
			Delay(1000);
			LCD_ShowString(2, 1, "       ");
		}
	}

}