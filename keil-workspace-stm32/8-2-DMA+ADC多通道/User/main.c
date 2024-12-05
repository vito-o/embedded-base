#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"


int main()
{
	OLED_Init();
	AD_init();
	
	OLED_ShowString(1, 1, "ch0:");
	OLED_ShowString(2, 1, "ch1:");
	OLED_ShowString(3, 1, "ch2:");
	OLED_ShowString(4, 1, "ch3:");
	
	while(1)
	{

		OLED_ShowNum(1, 5, AD_Value[0], 4);
		OLED_ShowNum(2, 5, AD_Value[1], 4);
		OLED_ShowNum(3, 5, AD_Value[2], 4);
		OLED_ShowNum(4, 5, AD_Value[3], 4);
		
		Delay_ms(100);
	}
}
