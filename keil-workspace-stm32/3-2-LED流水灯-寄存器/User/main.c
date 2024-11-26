#include "stm32f10x.h"                  // Device header

void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);
void Delay_s(uint16_t s);

int main()
{
	// 1.时钟配置
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	

	// 2.GPIO工作模式配置
	GPIOA->CRL &= ~GPIO_CRL_CNF0; 
	GPIOA->CRL |= GPIO_CRL_MODE0;

	GPIOA->CRL &= ~GPIO_CRL_CNF1; 
	GPIOA->CRL |= GPIO_CRL_MODE1;

	GPIOA->CRL &= ~GPIO_CRL_CNF2; 
	GPIOA->CRL |= GPIO_CRL_MODE2;

	// 3.在PA0,PA1,PA2输出高电平，默认关灯
	GPIOA->ODR |= GPIO_ODR_ODR0;
	GPIOA->ODR |= GPIO_ODR_ODR1;
	GPIOA->ODR |= GPIO_ODR_ODR2;



	while(1)
	{
		// LED1
		GPIOA->ODR &= ~GPIO_ODR_ODR0;	// 开灯
		Delay_ms(500);
		GPIOA->ODR |= GPIO_ODR_ODR0;
		// LED2
		GPIOA->ODR &= ~GPIO_ODR_ODR1;	// 开灯
		Delay_ms(500);
		GPIOA->ODR |= GPIO_ODR_ODR1;
		// LED3
		GPIOA->ODR &= ~GPIO_ODR_ODR2;	// 开灯
		Delay_ms(500);
		GPIOA->ODR |= GPIO_ODR_ODR2;
	}
	
}

// 延时函数，微秒作为单位，利用系统滴答定时器，72MHZ，一次抵达1/72 us
void Delay_us(uint16_t us)
{
	// 1.装载一个计数值，72 * us
	SysTick->LOAD = 72 * us;

	// 2.配置，使用系统时钟（1），计数结束不产生中断（0），使能定时器（1）
	SysTick->CTRL |= 0x05;

	// 3.等待计数值变为0，判断CTRL标志位COUNTFLAG是否为1
	while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0)
	{}

	// 4.关闭定时器
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
}

void Delay_ms(uint16_t ms)
{
	while(ms--)
	{
		Delay_us(1000);
	}
}

void Delay_s(uint16_t s)
{
	while(s--)
	{
		Delay_ms(1000);
	}
}