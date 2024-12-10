#include "Usart.h"

void Usart_init()
{
  // 1.时钟配置
	// 1.1 引脚时钟配置
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	
	// 1.2 串口1时钟配置
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	// 2.GPIO工作模式配置
	// 2.1 PA9=Tx(复用推挽 CNF=10 MODE=11)   PA10=Rx(浮空输入 CNF=01 MODE=00)
	GPIOA->CRH |= GPIO_CRH_CNF9_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
	GPIOA->CRH |= GPIO_CRH_MODE9;

	GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
	GPIOA->CRH |= GPIO_CRH_CNF10_0;
	GPIOA->CRH &= ~GPIO_CRH_MODE10;

	// 3.串口参数配置
	// 3.1 波特率配置 (115200)
	USART1->BRR = 0x271;
	// 3.2 串口使能，并使能接收和发送
	USART1->CR1 |= USART_CR1_UE;
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RE;
	// 3.3 配置一个字的长度8位
	USART1->CR1 &= ~USART_CR1_M;
	// 3.4 配置不需要校验位
	USART1->CR1 &= ~USART_CR1_PCE;
	// 3.5 配置停止位的长度
	USART1->CR2 &= ~USART_CR2_STOP;
	
}



void Usart1_SendChar(uint8_t byte)
{
	while((USART1->SR & USART_SR_TXE) == 0);
	
	USART1->DR = byte;
}

uint8_t Usart1_ReceiveChar(void)
{
	while((USART1->SR & USART_SR_RXNE) == 0);
	return USART1->DR;
}



void Usart1_SendString(uint8_t *str, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++)
	{
		Usart1_SendChar(str[i]);
	}
}

void Usart1_ReceiveString(uint8_t buff[], uint8_t *len)
{
	uint8_t i = 0;
	while(1)
	{
		//等待接收非空
		while((USART1->SR & USART_SR_RXNE) == 0)
		{
			// 在等待期间，判断是否收到空闲帧
			if (USART1->SR & USART_SR_IDLE)
			{
				*len = i;
				return;
			}
		}
		buff[i] = USART1->DR;
		i++;
	}
}
