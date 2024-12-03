#ifndef __TIME3_H__
#define __TIME3_H__

#include "stm32f10x.h"    

void TIME3_init(void);
void TIME3_Start(void);
void TIME3_Stop(void);

double TIME3_GetPWMCycle(void);
double TIME3_GetPWMFreq(void);
double TIME3_GetDutyCycle(void);

#endif
