#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"                  // Device header

void Led_init(void);

void Led1_on(void);
void Led1_off(void);
void Led1_toggle(void);

void Led2_on(void);
void Led2_off(void);
void Led2_toggle(void);

#endif
