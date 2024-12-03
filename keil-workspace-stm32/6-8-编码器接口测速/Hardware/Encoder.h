#ifndef __Encoder_H
#define __Encoder_H

#include "stm32f10x.h"                  // Device header

void Encoder_init(void);

int16_t Encoder_Get(void);

#endif
