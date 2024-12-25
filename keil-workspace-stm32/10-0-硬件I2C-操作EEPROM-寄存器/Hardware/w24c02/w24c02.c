#include "w24c02.h"



void w24c02_init()
{
  i2c_Init();
}



void w24c02_WriteByte(uint8_t addr, uint8_t byte)
{
	i2c_Start();
	
	i2c_SendAddr(ADDR);
	
	i2c_SendByte(addr);
	
	i2c_SendByte(byte);
	
	i2c_Stop();
	
	Delay_ms(5);
}
	
uint8_t w24c02_ReadByte(uint8_t addr)
{
	i2c_Start();
	i2c_SendAddr(ADDR);
	i2c_SendByte(addr);

	
	i2c_Start();
	i2c_SendAddr(ADDR+1);
	
	i2c_NACK();		// 先设置非应答信号  说明只接收一个
	i2c_Stop();		// 设置结束信号
	
	uint8_t byte = i2c_ReadByte(); // 接收数据
	
	return byte;
}

	
	
void w24c02_WriteBytes(uint8_t addr, uint8_t *bytes, uint8_t len)
{
	
	i2c_Start();
	
	i2c_SendAddr(ADDR);
	
	i2c_SendByte(addr);
	for (uint8_t i = 0; i < len; i++)
	{
		i2c_SendByte(bytes[i]);
	}
	
	i2c_Stop();
	
	Delay_ms(5);
}
	
void w24c02_ReadBytes(uint8_t addr, uint8_t *bytes, uint8_t len)
{
	i2c_Start();
	i2c_SendAddr(ADDR);
	i2c_SendByte(addr);

	
	i2c_Start();
	i2c_SendAddr(ADDR+1);
	
	for (uint8_t i = 0; i < len; i++)
	{
		if (i < len -1)
		{
			i2c_ACK();
		}
		else 
		{
			i2c_NACK();		// 先设置非应答信号  说明只接收一个
			i2c_Stop();		// 设置结束信号
		}
		
		bytes[i] = i2c_ReadByte(); // 接收数据

	}
}
