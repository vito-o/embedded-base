#include "Encoder.h"

// 旋钮 控制 引脚6|7 通过定时器控制cnt数字增加或减小
void Encoder_init(void)
{
	// 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// GPIOA Pin_6|7  引脚定义， 引脚输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 定时器
	
	
	// 时基单元初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元使用
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;								// 计数周期，即ARR的值 ARR：（Auto-Reload Register，自动重装载寄存器） ARR 是定时器的最大计数值。
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;								// 预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	// 输入捕获输出化
	TIM_ICInitTypeDef TIM_ICInitTypeStructure;
	TIM_ICStructInit(&TIM_ICInitTypeStructure);
	TIM_ICInitTypeStructure.TIM_Channel = TIM_Channel_1;								// 配置通道
	TIM_ICInitTypeStructure.TIM_ICFilter = 0xF;													// 滤波，可以过滤信号抖动
	TIM_ICInit(TIM3, &TIM_ICInitTypeStructure);
	
	TIM_ICInitTypeStructure.TIM_Channel = TIM_Channel_2;								// 配置通道
	TIM_ICInitTypeStructure.TIM_ICFilter = 0xF;													// 滤波，可以过滤信号抖动
	TIM_ICInit(TIM3, &TIM_ICInitTypeStructure);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
																																					
	// TIM使能
	TIM_Cmd(TIM3, ENABLE);										
}

int16_t Encoder_Get()
{
	int16_t temp = 0;
	temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return temp;
}
