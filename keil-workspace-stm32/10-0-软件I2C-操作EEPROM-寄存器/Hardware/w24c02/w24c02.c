#include "w24c02.h"



void w24c02_init()
{
  i2c_Init();
}



void w24c02_WriteByte(uint8_t addr, uint8_t byte)
{
	i2c_Start();
	
	i2c_SendByte(ADDR);
	uint8_t ack = i2c_WaitAck();
	if (ack == ACK)
	{
		i2c_SendByte(addr);
		i2c_WaitAck();
		
		i2c_SendByte(byte);
		i2c_WaitAck();
		
		i2c_Stop();
	}
	
	Delay_ms(5);
}
	
uint8_t w24c02_ReadByte(uint8_t addr)
{
	i2c_Start();
	
	i2c_SendByte(ADDR);
	i2c_WaitAck();

	i2c_SendByte(addr);
	i2c_WaitAck();
	
	
	i2c_Start();
	
	i2c_SendByte(ADDR+1);
	i2c_WaitAck();

	i2c_SendByte(addr);
	i2c_WaitAck();
		
	uint8_t byte = i2c_ReadByte();
	i2c_NACK();
		
	i2c_Stop();
	
	return byte;
}

	
	
void w24c02_WriteBytes(uint8_t addr, uint8_t *bytes, uint8_t len)
{
	i2c_Start();
	
	i2c_SendByte(ADDR);
	uint8_t ack = i2c_WaitAck();
	if (ack == ACK)
	{
		i2c_SendByte(addr);
		i2c_WaitAck();
		
		for (uint8_t i = 0; i < len; i++)
		{
			i2c_SendByte(bytes[i]);
			i2c_WaitAck();
		}
		
		i2c_Stop();
	}
	
	Delay_ms(5);
}
	
void w24c02_ReadBytes(uint8_t addr, uint8_t *bytes, uint8_t len)
{
	i2c_Start();
	
	i2c_SendByte(ADDR);
	i2c_WaitAck();

	i2c_SendByte(addr);
	i2c_WaitAck();
	
	
	i2c_Start();
	
	i2c_SendByte(ADDR+1);
	i2c_WaitAck();

	i2c_SendByte(addr);
	i2c_WaitAck();
	
	for (uint8_t i = 0; i < len; i++)
	{
		bytes[i] = i2c_ReadByte();
		
		if (i < len - 1)
		{
			i2c_ACK();
		}
		else
		{
			i2c_NACK();
		}
	}
	
	i2c_Stop();
}
