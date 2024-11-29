#include "delay.h"
#include "time2.h"

uint8_t i;

int main()
{
	//Led_init();
	TIME2_init();
	TIM2_Start();
	
	// 往复流水灯
	while(1)
	{
		for(i = 0;i<100;i++)
		{
			TIM2_SetDutyCycle(i);
			Delay_ms(20);
		}
		for(i = 0;i<100;i++)
		{
			TIM2_SetDutyCycle(100-i);
			Delay_ms(20);
		}
	}
	
}
