#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;	

int main()
{
	OLED_Init();
	Serial_init();
	
	OLED_ShowString(1, 1, "DATA=");
	
	while(1)
	{
		if (Serial_GetRxFlag() == 1)
		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
			
			OLED_ShowNum(1, 6, RxData, 2);
		}
		
		OLED_ShowString(2, 1, "Running");
		Delay_ms(100);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		__WFI();		// 执行WFI命令，cpu睡眠，并等待中断唤醒
	}
}
