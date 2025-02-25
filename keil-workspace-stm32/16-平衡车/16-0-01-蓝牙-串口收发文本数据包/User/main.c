#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Led.h"
#include <string.h>
#include "Systick.h"

uint8_t keyNum;	

int main()
{
	OLED_Init();
	
	Serial_init();
	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");
	
//	Systick_init();
//	Systick_start();
	Serial_SendString("AT+ENLOG\r\n");
	
	while(1)
	{
		if (Serial_RxFlag == 1)
		{
			OLED_ShowString(4, 1, "                     ");
			OLED_ShowString(4, 1, Serial_RxPacket);
			
			clear_RxPacket();
			Serial_RxFlag = 0;
		}
	}
}
