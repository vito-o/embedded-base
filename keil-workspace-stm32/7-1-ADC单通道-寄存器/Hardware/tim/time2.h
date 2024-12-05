#ifndef __TIME2_H__
#define __TIME2_H__

#include "stm32f10x.h"    

void TIME2_init(void);
void TIME2_Start(void);
void TIME2_Stop(void);
void TIME2_SetDutyCycle(uint8_t dutyCycle);

#endif
