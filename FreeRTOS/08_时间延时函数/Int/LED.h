#ifndef __LED_H
#define __LED_H

#include "gpio.h"

#define LED uint16_t

void LED_Turn_on(LED led);
void LED_Turn_off(LED led);
void LED_Toggle(LED led);

void LED_Turn_off_all(LED led[], uint8_t len);

#endif // __LED_H

