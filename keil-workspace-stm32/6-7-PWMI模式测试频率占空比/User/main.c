#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PWM.h"
#include "IC.h"
#include "Delay.h"

uint16_t i;

int main()
{
	OLED_Init();
	PWM_init();
	IC_init();

	OLED_ShowString(1, 1, "Freq:00000HZ");
	OLED_ShowString(2, 1, "Duty:00%");
	
	PWM_SetPrescaler(720 - 1); 		// PWM频率   Freq = 72M / (PSC + 1)/100;
	PWM_SetCompare1(30);					// PWM占空比Duty = CCR / 100;
	
	while(1)
	{
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);
		OLED_ShowNum(2, 6, IC_GetDuty(), 2);
	}
}

