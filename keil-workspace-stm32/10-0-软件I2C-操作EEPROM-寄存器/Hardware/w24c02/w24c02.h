#ifndef __W24C02_H__
#define __W24C02_H__

#include "stm32f10x.h"    
#include "i2c.h"
#include "string.h"

#define ADDR 0xA0

void w24c02_init(void);

void w24c02_WriteByte(uint8_t addr, uint8_t byte);
uint8_t w24c02_ReadByte(uint8_t addr);

void w24c02_WriteBytes(uint8_t addr, uint8_t *bytes, uint8_t len);
void w24c02_ReadBytes(uint8_t addr, uint8_t *bytes, uint8_t len);


#endif
