#ifndef __COUNTSENSOR_H
#define __COUNTSENSOR_H

#include "stm32f10x.h"                  // Device header

void CountSensor_init(void);

uint16_t CountSensor_Get(void);

#endif
