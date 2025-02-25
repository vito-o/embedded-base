#include "IC.h"
// GPIOA pin_6 接收pwm波形
// 通过在PWM模块中生成一个pwm波形，然后在当前模块接收波形，然后计算出当前波形
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

void IC_init(void)
{
	// 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// GPIOA Pin_6  引脚定义， 引脚输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 定时器
	
	// 配置时钟源
	TIM_InternalClockConfig(TIM3);	// 选择TIM3为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	// 时基单元初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;					// 时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元使用
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 		// 计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;										// 计数周期，即ARR的值 ARR：（Auto-Reload Register，自动重装载寄存器） ARR 是定时器的最大计数值。
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;										// 预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	// 输入捕获输出化
	TIM_ICInitTypeDef TIM_ICInitTypeStructure;
	TIM_ICInitTypeStructure.TIM_Channel = TIM_Channel_1;								// 配置通道
	TIM_ICInitTypeStructure.TIM_ICFilter = 0xF;													// 滤波，可以过滤信号抖动
	TIM_ICInitTypeStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;			// 上升沿触发
	TIM_ICInitTypeStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;						// 捕获分频，选择不分频
	TIM_ICInitTypeStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // 输入信号交叉，选择不交叉
	TIM_ICInit(TIM3, &TIM_ICInitTypeStructure);
	TIM_PWMIConfig(TIM3, &TIM_ICInitTypeStructure);											// 将结构体变量交给TIM_PWMIConfig，配置TIM3的输入捕获通道
																																			// 此函数同时会把另一个通道配置为相反的配置，实现PWMI模式
	// 选择触发源及从模式
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);												// 触发源选择TI1FP1
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);											// 从模式选择复位， 即TI1产生上升沿时，会触发CNT归零
																																					
	// TIM使能
	TIM_Cmd(TIM3, ENABLE);																							// TIM2,定时器开始运行
}

// 获取输入捕获的频率
uint16_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM3)+1);													// 测周法得到频率fx = fc / N，这里不执行+1操作也可以
}

uint16_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3)+1)*100 / (TIM_GetCapture1(TIM3)+1);		// 占空比Duty = CCR2 / CCR1 * 100，这里不执行+1的操作也可
}
