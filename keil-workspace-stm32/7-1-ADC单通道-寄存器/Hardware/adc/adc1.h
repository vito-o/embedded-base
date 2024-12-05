#ifndef __ADC1_H__
#define __ADC1_H__

#include "stm32f10x.h"    

void Driver_ADC1_Init(void);

void Driver_ADC1_StartConvert(void);

double Driver_ADC1_ReadV(void);


#endif
