#ifndef __AD_H
#define __AD_H

#include "stm32f10x.h"                  // Device header

extern uint16_t AD_Value[4];

void AD_init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);

#endif
