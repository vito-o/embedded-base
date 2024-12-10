#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Led.h"
#include <string.h>

uint8_t keyNum;	

int main()
{
	OLED_Init();
	Serial_init();
	Led_init();
	
	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");
	
	while(1)
	{
		if (Serial_RxFlag == 1)
		{
			OLED_ShowString(4, 1, "                     ");
			OLED_ShowString(4, 1, Serial_RxPacket);
			
			if (strcmp(Serial_RxPacket, "LED_ON") == 0)
			{
				Led1_on();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2, 1, "                    ");
				OLED_ShowString(2, 1, "LED_ON_OK");
			}
			else if (strcmp(Serial_RxPacket, "LED_OFF") == 0)
			{
				Led1_off();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2, 1, "                    ");
				OLED_ShowString(2, 1, "LED_OFF_OK");
			}
			else
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "ERROR_COMMAND");
			}
			
			Serial_RxFlag = 0;
		}
	}
}
