#ifndef __LED_H__
#define __LED_H__  

#include "gpio.h"  

#define LED uint16_t

void Led_on(LED led);
void Led_off(LED led);
void LED_onAll(LED leds[], uint8_t size);
void LED_offAll(LED leds[], uint8_t size);

#endif
