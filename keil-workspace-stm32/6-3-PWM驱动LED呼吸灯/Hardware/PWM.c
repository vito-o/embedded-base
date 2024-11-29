#include "PWM.h"
// GPIOA pin_0 输出pwm波形

/*
CK_PSC 时钟频率
PSC 预分频器
ARR 自动重装载寄存器
CCR 捕获/比较寄存器

							CK_PSC			
PWM频率 = ------------- / (ARR + 1)
							PSC + 1      

								CCR
PWM占空比 =  --------
							 ARR + 1
							 
									1
PWM分辨率 =  --------
               ARR + 1
							 
							 
现在要产生一个频率1KHZ 占空比为50% 分辨率为1%的PWM波形
ARR = 99
CCR = 50
PWM频率 	==  1000 = 72MHZ/PSC+1/100
					==  1000 00 = 72MHZ / PSC + 1
					==  1000 00 = 72 000 000 / PSC + 1
	PSC			=  720 - 1
*/	

void PWM_init(void)
{
	// 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// GPIOA Pin_0  引脚定义， 引脚输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 定时器
	
	// GPIO重映射（即端口冲突，更换端口输出pwm波形）
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//开启AFIO的时钟，重映射必须先开启AFIO的时钟
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); //将TIM2的引脚部分重映射，具体映射方案需要查看参考手册
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // 将JTAG引脚 作为普通GPIO引脚使用
	
	
	
	// 配置时钟源
	TIM_InternalClockConfig(TIM2);	// 选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	// 时基单元初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元使用
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;									// 计数周期，即ARR的值 ARR：（Auto-Reload Register，自动重装载寄存器） ARR 是定时器的最大计数值。
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;							// 预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 输出比较初始化
	TIM_OCInitTypeDef TIM_OCInitTypeStructure;
	TIM_OCStructInit(&TIM_OCInitTypeStructure);												// 结构体初始化
	
	TIM_OCInitTypeStructure.TIM_OCMode = TIM_OCMode_PWM1;							// 输出比较模式，选择PWM模式1
	TIM_OCInitTypeStructure.TIM_OCPolarity = TIM_OCPolarity_High;			// 输出极性，选择为高，输出电平不反转
	TIM_OCInitTypeStructure.TIM_OutputState = TIM_OutputState_Enable;	// 输出使能
	TIM_OCInitTypeStructure.TIM_Pulse = 0;														// 初始的CCR的值 （捕获/比较寄存器）
	TIM_OC1Init(TIM2, &TIM_OCInitTypeStructure);
	
	// TIM使能
	TIM_Cmd(TIM2, ENABLE);																						// TIM2,定时器开始运行
}

void PWM_SetCompare1(uint16_t compare)
{
	TIM_SetCompare1(TIM2, compare); 		// 设置CCR1的值
}
