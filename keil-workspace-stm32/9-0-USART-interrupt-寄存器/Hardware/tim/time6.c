#include "time6.h"
#include "led.h"

void TIME2_init()
{
  // 1.时钟配置  (STC32F103C8T6只有tim1~4 没有6，这里的例子暂时跑不通)
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;	

	// 2.设置预分频值，做7200分频，得到10000HZ
	TIM6->PSC = 7200 - 1; // PSC为0不分频  PSC为1为二分频
	
	// 3.设置自动重装值9999，表示计数10000次，产生一个uev 中断
	TIM6->ARR = 10000 - 1; // 自动重装值设定后，产生中段是在下一个上升沿产生所以多了一次，这里要减一
	
	// 4.更新中断使能
	TIM6->DIER |= TIM_DIER_UIE;
	
	// 5.NVIC配置
	NVIC_SetPriorityGrouping(3);
	NVIC_SetPriority(TIM6_IRQn, 2);
	NVIC_EnableIRQ(TIM6_IRQn);
	
	// 6.开启定时器
	TIM6->CR1 |= TIM_CR1_CEN;
}

void TIM6_IRQHandler(void)
{
	TIM6->SR &= ~TIM_SR_UIF; //设置为0
	
	Led_toggle(Led1);
}