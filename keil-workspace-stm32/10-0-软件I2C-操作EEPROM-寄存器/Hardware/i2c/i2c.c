#include "i2c.h"


void i2c_Init(void)
{
	// 开启时钟
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	// 开漏输出模式 MODE=11 CNF=01
	GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11);
	
	GPIOB->CRH |= (GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0);
	GPIOB->CRH &= ~(GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1);
	
}


void i2c_Start(void)
{
	// 先默认拉高
	SCL_HIGH;
	SDA_HIGH;
	Delay_us(10);
	
	SDA_LOW;
}

void i2c_Stop(void)
{
	SCL_HIGH;
	SDA_LOW;
	Delay_us(10);
	
	SDA_HIGH;
	Delay_us(10);
}


// 主机确认
void i2c_ACK(void)
{
	SCL_LOW;
	SDA_HIGH;
	
	Delay_us(10);
	
	SDA_LOW;
	Delay_us(10);
	
	SCL_HIGH;
	Delay_us(10);
	
	SCL_LOW;
	Delay_us(10);
	
	SDA_HIGH;
	Delay_us(10);
}
// 主机不确认
void i2c_NACK(void)
{
	SCL_LOW;
	SDA_HIGH;
	Delay_us(10);
	
	SCL_HIGH;
	Delay_us(10);
	
	SCL_LOW;
	Delay_us(10);
}
// 主机等待从设备发来应答信号
uint8_t i2c_WaitAck(void)
{
	SCL_LOW;
	SDA_HIGH;
	Delay_us(10);
	
	SCL_HIGH;
	Delay_us(10);
	
	uint8_t ack = ACK;
	if (READ_SDA) // 从引脚读取信号，判断从设备是否应答
	{
		ack = NACK;
	}
	
	SCL_LOW;
	Delay_us(10);
	
	return ack;
}


void i2c_SendByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		SCL_LOW;
		SDA_LOW;
		Delay_us(10);
		
		// 从高位到低位发
		if (byte & (0x80 >> i))
		{
			SDA_HIGH;
		}
		else 
		{
			SDA_LOW;
		}
		Delay_us(10);
		
		SCL_HIGH;
		Delay_us(10);
		
		SCL_LOW;
		Delay_us(10);
		
	}
}

uint8_t i2c_ReadByte(void)
{
	uint8_t byte = 0;
	
	for (uint8_t i = 0; i < 8; i++)
	{
		SCL_LOW;
		Delay_us(10);
		
		SCL_HIGH;
		Delay_us(10);
		
		// 从高位到地位接收
		if (READ_SDA)
		{
			byte |= 0x80 >> i;
		}
		Delay_us(10);
		
		SCL_LOW;
		Delay_us(10);
	}
	
	return byte;
}




