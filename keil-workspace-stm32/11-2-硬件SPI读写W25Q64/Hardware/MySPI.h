#ifndef __MYSPI_H
#define __MYSPI_H

#include "stm32f10x.h"                  // Device header

void MySPI_init(void);

// SPI开始
void MySPI_Start(void);

// SPI结束
void MySPI_Stop(void);

// SPI交换数据
uint8_t MySPI_SwapByte(uint8_t byteSend);



#endif
