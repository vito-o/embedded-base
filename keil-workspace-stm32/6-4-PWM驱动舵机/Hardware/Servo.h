#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"                  // Device header

void Servo_init(void);
void Servo_setAngle(float angle);

#endif
