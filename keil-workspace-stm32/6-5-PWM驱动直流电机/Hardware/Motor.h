#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"                  // Device header

void Motor_init(void);
void Motor_SetSpeed(int8_t speed);
#endif
