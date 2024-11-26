#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"    

#define Led1 GPIO_ODR_ODR0
#define Led2 GPIO_ODR_ODR1
#define Led3 GPIO_ODR_ODR2

void Led_init(void);
void Led_on(uint16_t led);
void Led_off(uint16_t led);
void LED_onAll(uint16_t leds[], uint8_t size);
void LED_offAll(uint16_t leds[], uint8_t size);
#endif
