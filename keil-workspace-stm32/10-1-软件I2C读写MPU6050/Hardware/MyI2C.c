#include "MyI2C.h"
#include "Delay.h"

// I2C 写SCL引脚电平
void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
	Delay_us(10);
}

// I2C 写SDA引脚电平
void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
	Delay_us(10);
}

// I2C 读SDA引脚电平
uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}


void MyI2C_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;				// 将PB10和PB11引脚初始化为开漏输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

// ---------协议---


void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);			// 释放SDA，确保SDA为高电平
	MyI2C_W_SCL(1);			// 释放SCL，确保SCL为高电平
	MyI2C_W_SDA(0);			// 在SCL为高电平期间，将SDA拉低，产生起始信号
	MyI2C_W_SCL(0);			// 起始后把SCL也拉低，即为占用总线，也为了方便总线时序的拼接
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);			// 拉低SDA，确保SDA为低电平
	MyI2C_W_SCL(1);			// 释放SCL，使SCL呈现高电平
	MyI2C_W_SDA(1);			// 在SCL为高电平期间，释放SDA，产生终止信号
}

void MyI2C_SendByte(uint8_t Byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		MyI2C_W_SDA(!!(Byte & (0x80 >> i)));	// 使用掩码方式取出Byte的指定一位数据并写入到SDA
		MyI2C_W_SCL(1);												// 释放SCL，从机在SCL高电平期间读取SDA值
		MyI2C_W_SCL(0);												// 拉低SCL，主机开始发送下一位数据
	}
}

uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t Byte = 0x00;
	MyI2C_W_SDA(1);	// 接收前，主机先确保释放SDA，避免干扰从机的数据发送
	
	for (uint8_t i = 0; i < 8; i++)
	{
		MyI2C_W_SCL(1);
		if (MyI2C_R_SDA()) {Byte |= (0X80 >> i);}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);												// 释放SCL，从机在SCL高电平期间读取SDA值
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	uint8_t AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}
