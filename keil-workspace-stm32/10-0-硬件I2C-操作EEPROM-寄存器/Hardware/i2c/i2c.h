#ifndef __i2c_H__
#define __i2c_H__

#include "stm32f10x.h"    
#include "delay.h"

#define ACK 0
#define NACK 1

#define OK 1
#define FAIL 0


void i2c_Init(void);

uint8_t i2c_Start(void);
void i2c_Stop(void);

void i2c_ACK(void);
void i2c_NACK(void);

uint8_t i2c_SendAddr(uint8_t addr);
uint8_t i2c_SendByte(uint8_t byte);
uint8_t i2c_ReadByte(void);



#endif
