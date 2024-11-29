#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PWM.h"
#include "Delay.h"

uint16_t i;

int main()
{
	OLED_Init();
	PWM_init();

	OLED_ShowString(1, 3, "num:");
	
	while(1)
	{
		for(i = 0; i < 100; i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for(i = 0; i < 100; i++)
		{
			PWM_SetCompare1(100-i);
			Delay_ms(10);
		}
		
		OLED_ShowNum(1, 7, i, 3);
		
	}
}

