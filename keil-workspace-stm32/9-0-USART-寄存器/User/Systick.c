#include "Systick.h"
#include "led.h"

void SysTick_init()
{
	// 1.设置重装载值，每1ms产生一次中断
	SysTick->LOAD = 72000 - 1;
	
	// 2.配置时钟源，AHB = 72MHZ
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;
	
	// 3. 使能中断
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
	
	// 4. 开启定时器
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
}

// 定义一个变量，用于计数
uint16_t count = 0;

// 中断服务程序
void SysTick_Handler(void)
{
	count++;
	if (count >= 1000)
	{
		count = 0;
		Led_toggle(Led1);
	}
}


