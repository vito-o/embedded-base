#ifndef __DRIVER_DMA_H
#define __DRIVER_DMA_H

#include "stm32f10x.h"                  // Device header

extern uint8_t isTransmitFinished;

void Driver_DMA1_init(void);
void Driver_DMA1_TransmitData(uint32_t srcAddr, uint32_t desAddr, uint16_t dataLen);


#endif
