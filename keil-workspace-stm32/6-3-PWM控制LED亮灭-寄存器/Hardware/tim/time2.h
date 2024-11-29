#ifndef __TIME2_H__
#define __TIME2_H__

#include "stm32f10x.h"    

void TIME2_init(void);
void TIM2_Start(void);
void TIM2_Stop(void);
void TIM2_SetDutyCycle(uint8_t dutyCycle);

#endif
