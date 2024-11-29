#include "Timer.h"
// 通过A0引脚产生计数信号，计数值达到设定值产生一次中断
void Timer_init(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//A0引脚数据输入，低电平置1
	GPIO_InitTypeDef GPIO_InitTypeStructure;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitTypeStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	
	
	// 配置时钟源
	//TIM_InternalClockConfig(TIM2);	// 选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
	// 配置外部时钟
	// 选择外部时钟模式2，时钟从TIM_ETR引脚输入
	// 注意tim2的ETR引脚固定为PA0，无法随意更改
	
	// TIM_ExtTRGPSC_OFF 表示不对外部触发信号进行预分频， 这个参数设置外部触发信号的预分频器。
	// TIM_ExtTRGPolarity_NonInverted 表示触发信号的极性为非反向（即高电平触发）。如果使用 TIM_ExtTRGPolarity_Inverted，则为反向极性（即低电平触发）。设置外部触发信号的极性。 
	// 0x0F 这个参数设置外部触发的滤波器值。0x0F 代表一个滤波器值，这个值用于控制输入信号的噪声过滤。滤波器的作用是忽略一些短时间的噪声信号，确保只有符合条件的有效触发信号才能触发定时器。
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);
	
	// 时基单元初始化 - 设置1秒计数一次
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元使用
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;								  // 计数周期，即ARR的值 ARR：（Auto-Reload Register，自动重装载寄存器） ARR 是定时器的最大计数值。
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;								// 预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 中断输出配置
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);														// 清除定时器更新标志位
																																	// TIM_TimeBaseInit函数末尾，手动产生了更新事件
																																	// 若不清除此标志位，则开启中断后，回立刻进入一次中断
																																	// 如果不介意此问题也可以不清除此标志位
	
	TIM_ITConfig(TIM2, TIM_FLAG_Update, ENABLE);										// 开启TIM2的更新中断
	
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

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
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
