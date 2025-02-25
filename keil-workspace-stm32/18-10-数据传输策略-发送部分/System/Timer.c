#include "Timer.h"

void Timer_init(void)
{
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 配置时钟源
	TIM_InternalClockConfig(TIM2);	// 选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	// 时基单元初始化 - 设置1秒计数一次
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元使用
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;								// 计数周期，即ARR的值 ARR：（Auto-Reload Register，自动重装载寄存器） ARR 是定时器的最大计数值。
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;							// 预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 中断输出配置
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);														// 清除定时器更新标志位
																																	// TIM_TimeBaseInit函数末尾，手动产生了更新事件
																																	// 若不清除此标志位，则开启中断后，回立刻进入一次中断
																																	// 如果不介意此问题也可以不清除此标志位
	
	TIM_ITConfig(TIM2, TIM_FLAG_Update, ENABLE);										// 开启TIM2的中断
	
	// NVIC中断分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);									// 配置NVIC为分组2
																																	// 即抢占优先级范围： 0~3， 响应优先级范围0~3
	// NVIC配置		
	NVIC_InitTypeDef NVIC_InitTypeStructure;
	NVIC_InitTypeStructure.NVIC_IRQChannel = TIM2_IRQn;							// 配置NVIC的TIM2线
	NVIC_InitTypeStructure.NVIC_IRQChannelCmd = ENABLE;							// 使能
	NVIC_InitTypeStructure.NVIC_IRQChannelPreemptionPriority = 2;		// 抢占优先级
	NVIC_InitTypeStructure.NVIC_IRQChannelSubPriority = 1;					// 响应优先级
	NVIC_Init(&NVIC_InitTypeStructure);
	
	// TIM使能
	TIM_Cmd(TIM2, ENABLE);																					// TIM2,定时器开始运行
	
}

/*
// 定时器中断函数，可以复制到使用它的地方
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/
