#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

#define ch0 ADC_Channel_0
#define ch1 ADC_Channel_1
#define ch2 ADC_Channel_2
#define ch3 ADC_Channel_3

uint16_t ad0, ad1, ad2, ad3;
uint16_t adValue;

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
		ad0 = AD_GetValue(ch0);
		ad1 = AD_GetValue(ch1);
		ad2 = AD_GetValue(ch2);
		ad3 = AD_GetValue(ch3);
		
		OLED_ShowNum(1, 5, ad0, 4);
		OLED_ShowNum(2, 5, ad1, 4);
		OLED_ShowNum(3, 5, ad2, 4);
		OLED_ShowNum(4, 5, ad3, 4);
		
		Delay_ms(100);
	}
}
