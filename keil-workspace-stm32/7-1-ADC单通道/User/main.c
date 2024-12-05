#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t adValue;
float voltage;

int main()
{
	OLED_Init();
	AD_init();
	
	OLED_ShowString(1, 1, "adValue:");
	OLED_ShowString(2, 1, "voltage:0.00V");
	
	while(1)
	{
		adValue = AD_GetValue();
		voltage = (float)adValue / 4095 * 3.3;
		
		OLED_ShowNum(1, 9, adValue, 4);
		OLED_ShowNum(2, 9, voltage, 1);
		OLED_ShowNum(2, 11, (uint16_t)voltage * 100 % 100, 2);
		
		Delay_ms(100);
	}
}
