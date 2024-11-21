#include "stm32f10x.h"                  // Device header


int main()
{
	/*
	// 配置寄存器的方式进行电灯操作
	RCC->APB2ENR = 0x00000010; //时钟配置，开启APB2模块
	GPIOC->CRH = 0x00300000;
	//GPIOC->ODR = 0x00000000;
	GPIOC->ODR = 0x00002000;
	
	
	//尚硅谷
	//1.时钟配置， 不同模块可以配置不同时钟，不给时钟不耗电
	//  APB2时钟配置，开启时钟
	//  0x40023000 + 0x0C ==  基地址 + 偏移地址
	//  *(uint32_t *)(0x40023000 + 0x0C) = 4; 
	//2.GPIO工作模式配置 
	//  因为是32位，13引脚配置在23~20，所以最终值为  0x00300000
	//  因为要设置的是GPIOC 所以基地址为：0x40011000, 0x04是因为13引脚在端口配置高寄存器（RCH）它的偏移地址为：0x04
	//  *(uint32_t *)(0x40011000 + 0x04) = 0x00300000;
	//3.PC13配置低电平（参照电路图）
	//  端口输出数据寄存器ODR,                                                  1101 1111 1111 1111
	//  基地址为：0x40011000     偏移地址为：0x0C(h：h为汇编中的写法)       值为：0x0000DFFF
	//  *(uint32_t *)(0x40011000 + 0x0C) = 0x0000DFFF;
	//4.死循环保持状态
	//  while(1);
	
	*/
	
	//时钟配置， 不同模块可以配置不同时钟，不给时钟不耗电
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	
	while(1)
	{
	
	}
	
}
