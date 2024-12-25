#ifndef __i2c_H__
#define __i2c_H__

#include "stm32f10x.h"    
#include "delay.h"

#define ACK 0
#define NACK 1

#define SCL_HIGH (GPIOB->ODR |= GPIO_ODR_ODR10)
#define SCL_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR10)

#define SDA_HIGH (GPIOB->ODR |= GPIO_ODR_ODR11)
#define SDA_LOW  (GPIOB->ODR &= ~GPIO_ODR_ODR11)

#define READ_SDA (GPIOB->IDR & GPIO_IDR_IDR11)

void i2c_Init(void);

void i2c_Start(void);
void i2c_Stop(void);

void i2c_ACK(void);
void i2c_NACK(void);
uint8_t i2c_WaitAck(void);

void i2c_SendByte(uint8_t byte);
uint8_t i2c_ReadByte(void);



#endif
