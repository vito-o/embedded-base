#ifndef __Systick_H
#define __Systick_H

#include "stm32f10x.h"                  // Device header

void Systick_init(void);
void Systick_start(void);
void Systick_stop(void);


#endif
