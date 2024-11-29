#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"                  // Device header

void PWM_init(void);
void PWM_SetCompare1(uint16_t compare);

#endif
