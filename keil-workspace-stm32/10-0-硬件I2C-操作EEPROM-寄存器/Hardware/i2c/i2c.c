#include "i2c.h"


void i2c_Init(void)
{
	// 开启时钟
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	
	// 复用开漏输出模式 MODE=11 CNF=11
	GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_CNF10 | GPIO_CRH_CNF11);
	
	// 3.设置I2C2
	// 3.1 配置工作模式
	I2C2->CR1 &= ~I2C_CR1_SMBUS;
	
	// 3.2 配置i2c设备提供的时钟频率36MHZ
	I2C2->CR2 |= 36 << 0;
	
	// 3.3 配置标准模式=0 or 快速模式=1
	I2C2->CCR &= ~I2C_CCR_FS;
	
	// 3.4 配置I2C产生的时钟频率 100K or 400K
	//     Thigh = CCR * Tcplk1      Tcplk1 = 输入时钟频率36mhz
	//     CCR = Thigh / Tcplk1 = 100K / 36MHZ = 5us / (1/36)us = 180
	I2C2->CCR |= 180 << 0;
	
	// 3.5 时钟信号的上升沿
	//     SCL 的最大上升时间 是 I2C 总线上时钟信号从 低电平 上升到 高电平 所需的最大允许时间。
	//     100kHZ的时候要求最大上升沿不超过1us（手册）
	//     时钟频率是36MHZ则  写入： 1/(1/36) + 1 = 37
	//     其实就是计算 最大上升沿时间/ 时钟周期 + 1
	I2C2->TRISE |= 37;
	
	// 3.6 使能I2C
	I2C2->CR1 |= I2C_CR1_PE;
}


uint8_t i2c_Start(void)
{
	I2C2->CR1 |= I2C_CR1_START;
	
	uint16_t timeout = 0xffff;
	while(((I2C2->SR1 & I2C_SR1_SB) == 0) && timeout)  // – 当发送出起始条件时该位被置’1’。
	{
		timeout--;
	}
	return timeout ? OK : FAIL;
}

void i2c_Stop(void)
{
	I2C2->CR1 |= I2C_CR1_STOP;
}


// 主机确认
void i2c_ACK(void)
{
	I2C2->CR1 |= I2C_CR1_ACK;
}
// 主机不确认
void i2c_NACK(void)
{
	I2C2->CR1 &= ~I2C_CR1_ACK;
}


uint8_t i2c_SendAddr(uint8_t addr)
{
	// 把要发送的数据写入到数据寄存器
	I2C2->DR = addr;
	
	uint16_t timeout = 0xffff;
	while(((I2C2->SR1 & I2C_SR1_ADDR) == 0) && timeout)  // – 当发送出起始条件时该位被置’1’。
	{
		timeout--;
	}
	
	if (timeout)
	{
		I2C2->SR2;
	}
	
	return timeout ? OK : FAIL;
}


uint8_t i2c_SendByte(uint8_t byte)
{
	uint16_t timeout = 0xfffff;
	while(((I2C2->SR1 & I2C_SR1_TXE) == 0) && timeout)  //判断数据寄存器是否为空，空了就可以发数据
	{
		timeout--;
	}
	// 把要发送的数据写入到数据寄存器
	I2C2->DR = byte;
	
	
	timeout = 0xfffff;
	while(((I2C2->SR1 & I2C_SR1_BTF) == 0) && timeout)	// 判断字节发送是否结束
	{
		timeout--;
	}
	return timeout ? OK : FAIL;
}

uint8_t i2c_ReadByte(void)
{
	uint16_t timeout = 0xfffff;
	
	while(((I2C2->SR1 & I2C_SR1_RXNE) == 0) && timeout) // 判断数据寄存器是否为空，有值才可以读取数据
	{
		timeout--;
	}
	
	uint8_t byte = timeout ? I2C2->DR : 0;
	return byte;
}




