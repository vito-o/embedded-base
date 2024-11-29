#include "time2.h"
#include "led.h"

void TIME2_init()
{
  // 1.时钟配置  (STC32F103C8T6只有tim1~4
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	
	// 2.GPIO工作模式， 复用推挽输出 CNF-10, MODE-11
	GPIOA->CRL |= GPIO_CRL_MODE1;
	GPIOA->CRL |= GPIO_CRL_CNF1_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF1_0;

	// 配置时基单元
	// 2.设置预分频值，做7200分频，得到10000HZ , 这里最终目的是产生的频率必须大于肉眼所能看见的过度效果 类似电视屏幕刷新率
	TIM2->PSC = 7200 - 1; // PSC为0不分频  PSC为1为二分频
	
	// 3.设置自动重装值99，表示计数100次，产生一个uev 中断
	TIM2->ARR = 100 - 1; // 自动重装值设定后，产生中段是在下一个上升沿产生所以多了一次，这里要减一
	
	// 4.设置计数方向， 向上计数
	TIM2->CR1 &= ~TIM_CR1_DIR;
	
	// 配置输出比较单元
	// 5.设置通道2的CCR
	TIM2->CCR2 = 0;
	
	// 6.设置通道2为输出模式
	TIM2->CCMR1 &= ~TIM_CCMR1_CC2S;
	
	// 7.配置通道2为PWM1模式，
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_2;
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2M_0;
	
	// 8.配置使能信号
	TIM2->CCER &= ~TIM_CCER_CC2E;
}


// 开启定时器
void TIM2_Start(void)
{
	TIM2->CR1 |= TIM_CR1_CEN;
}

// 关闭定时器
void TIM2_Stop(void)
{
	TIM2->CR1 &= ~TIM_CR1_CEN;
}

// 设置占空比的函数
void TIM2_SetDutyCycle(uint8_t dutyCycle)
{
	TIM2->CCR2 = dutyCycle;
}
