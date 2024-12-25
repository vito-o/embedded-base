#include "w24c02.h"

void w24c02_init()
{
  MX_I2C2_Init();
}



void w24c02_WriteByte(uint8_t addr, uint8_t byte)
{
	HAL_I2C_Mem_Write(&hi2c2, ADDR, addr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);
	
	HAL_Delay(5);
}
	
uint8_t w24c02_ReadByte(uint8_t addr)
{
	uint8_t byte;
	HAL_I2C_Mem_Read(&hi2c2, ADDR+1, addr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);
	
	return byte;
}

	
	
void w24c02_WriteBytes(uint8_t addr, uint8_t *bytes, uint8_t len)
{
	HAL_I2C_Mem_Write(&hi2c2, ADDR, addr, I2C_MEMADD_SIZE_8BIT, bytes, len, 1000);
	HAL_Delay(5);
}
	
void w24c02_ReadBytes(uint8_t addr, uint8_t *bytes, uint8_t len)
{
	HAL_I2C_Mem_Read(&hi2c2, ADDR+1, addr, I2C_MEMADD_SIZE_8BIT, bytes, len, 1000);
}
