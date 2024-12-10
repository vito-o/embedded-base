#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

int main()
{
	OLED_Init();
	Serial_init();
	
	Serial_SendByte(0x41);
	
	uint8_t arr[] = {0x42, 0x43, 0x44, 0x45};
	Serial_SendArray(arr, 4);
	
	Serial_SendString("\r\nNum1=");
	Serial_SendNumber(111, 3);
	
	printf("\r\nNum2=%d", 222);
	
	
	char str[100];
	sprintf(str, "\r\nNum3=%d", 333);
	Serial_SendString(str);
	
	Serial_Printf("\r\nNum4=%d", 444);
	Serial_Printf("\r\n");
	
	OLED_ShowString(1, 1, "running");
	while(1)
	{
		
	}
}
