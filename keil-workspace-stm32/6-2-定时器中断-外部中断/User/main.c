#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Timer.h"
// 6-2 定时器外部时钟， 将对射式红外传感器当作时钟
uint16_t num;

int main()
{
	OLED_Init();
	Timer_init();

	OLED_ShowString(1, 3, "Hello world!");
	
	while(1)
	{
		OLED_ShowNum(2, 1, num, 5);
		OLED_ShowNum(3, 1, Timer_GetCounter(), 5);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
