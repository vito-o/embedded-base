#include "Systick.h"
#include "OLED.h"

void Systick_init(void)
{
	// 开启 TIM2 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// 配置定时器
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;  // 设置为 1 秒
	TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;  // 设置时钟预分频器
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	// 中断输出配置
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	// 开启定时器中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// NVIC中断分组
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

void Systick_start()
{
	// 启动定时器
	TIM_Cmd(TIM2, ENABLE);
}
	
void Systick_stop()
{
	// 启动定时器
	TIM_Cmd(TIM2, DISABLE);
}

void Systick_setCounter(uint16_t count)
{
	TIM_SetCounter(TIM2, 0);
}

// 定时器中断处理函数
void TIM2_IRQHandler(void) {
	static uint16_t i = 0;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			
			i++;
			OLED_ShowNum(2, 1, i, 5);
		
			if (i > 5)
			{
				
				i = 0;
			}
	}
}
