#include "Led.h"

void Led_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

void Led1_on()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void Led1_off()
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void Led1_toggle()
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
	{
		Led1_off();
	}
	else
	{
		Led1_on();
	}
}

void Led2_on()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void Led2_off()
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void Led2_toggle()
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
	{
		Led2_off();
	}
	else
	{
		Led2_on();
	}
}
