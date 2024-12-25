#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_init(void);

uint8_t getKey(void);



#endif
