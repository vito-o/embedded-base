#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"                  // Device header

void Encoder_init(void);
int16_t Envoder_Get(void);

#endif
