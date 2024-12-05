#ifndef __MYDMA_H
#define __MYDMA_H

#include "stm32f10x.h"                  // Device header

void MyDMA_init(uint32_t dataA, uint32_t dataB, uint16_t size);
void MyDMA_Transfer(void);

#endif
