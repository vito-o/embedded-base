#include "time3.h"
// GPIOA-> 6
void TIME3_init()
{
  // 1.时钟配置  (STC32F103C8T6只有tim1~4
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	
	
	// 2.配置GPIOA-6引脚
	// 2.1 GPIO工作模式， 浮空输入 CNF-01, MODE-00
	GPIOA->CRL &= ~GPIO_CRL_MODE6;
	GPIOA->CRL &= ~GPIO_CRL_CNF6_1;
	GPIOA->CRL |= GPIO_CRL_CNF6_0;

	// 3.配置时基单元
	// 3.1 设置预分频值
	TIM3->PSC = 72 - 1; // PSC为0不分频  PSC为1为二分频
	
	// 3.2 设置自动重装值
	TIM3->ARR = 65536 - 1; // 自动重装值设定后，产生中段是在下一个上升沿产生所以多了一次，这里要减一
	
	// 3.3 设置计数方向， 向上计数
	TIM3->CR1 &= ~TIM_CR1_DIR;
	
	// 4.配置输入捕获
	// 4.1 TI1的选择：把CH1直接连接到TI1
	TIM3->CR2 &= ~TIM_CR2_TI1S;
	// 4.2 信号的输入滤波器： 不进行滤波
	TIM3->CCMR1 &= ~TIM_CCMR1_IC1F;
	// 4.3 边缘检测器，上升沿捕获
	TIM3->CCER &= ~TIM_CCER_CC1P;
	//     通道2： 下降沿触发
	TIM3->CCER |= TIM_CCER_CC2P;
	
	// 4.4 通道1配置为输入，并把信号映射到IC1
	TIM3->CCMR1 |= TIM_CCMR1_CC1S_1;
	TIM3->CCMR1 &= ~TIM_CCMR1_CC1S_0;
	//     通道2： 输入映射位TI1 10
	TIM3->CCMR1 |= TIM_CCMR1_CC2S_1;
	TIM3->CCMR1 &= ~TIM_CCMR1_CC2S_0;
	
	// 4.5 对信号做分频，（预分频） (信号频率比较高的时候需要做分频)
	TIM3->CCMR1 &= ~TIM_CCMR1_IC1PSC;
	//     通道2： 不分频 00
	TIM3->CCMR1 &= ~TIM_CCMR1_IC2PSC;
	
	// 4.6 通道1输入捕获使能
	TIM3->CCER |= TIM_CCER_CC1E;
	//     通道2： 
	TIM3->CCER |= TIM_CCER_CC2E;
	
	// 4.7配置触发输入信号TRGI TS - 101
	TIM3->SMCR |= TIM_SMCR_TS_2;
	TIM3->SMCR &= ~TIM_SMCR_TS_1;
	TIM3->SMCR |= TIM_SMCR_TS_0;
	
	// 4.8配置从模式为复位模式SMS - 100
	TIM3->SMCR |= TIM_SMCR_SMS_2;
	TIM3->SMCR &= ~TIM_SMCR_SMS_1;
	TIM3->SMCR &= ~TIM_SMCR_SMS_0;
	
//	// 4.6 开启捕获中断
//	TIM3->DIER |= TIM_DIER_CC1IE;
//	
//	// 5.设置NVIC配置，为中断配置
//	NVIC_SetPriorityGrouping(3);
//	NVIC_SetPriority(TIM3_IRQn, 3);
//	NVIC_EnableIRQ(TIM3_IRQn);
}


// 开启定时器
void TIME3_Start(void)
{
	TIM3->CR1 |= TIM_CR1_CEN;
}

// 关闭定时器
void TIME3_Stop(void)
{
	TIM3->CR1 &= ~TIM_CR1_CEN;
}

// 返回pwm的周期ms
double TIME3_GetPWMCycle(void)
{
	return TIM3->CCR1 / 1000.0;
}

// 返回pwm的频率
double TIME3_GetPWMFreq(void)
{	// 1000000 => 1MHZ
	return 1000000 / TIM3->CCR1;
}

// 返回占空比
double TIME3_GetDutyCycle(void)
{	
	return TIM3->CCR2 / TIM3->CCR1;
}


