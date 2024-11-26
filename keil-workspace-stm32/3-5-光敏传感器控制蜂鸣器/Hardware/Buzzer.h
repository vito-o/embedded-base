#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f10x.h"                  // Device header

void Buzzer_init(void);

void Buzzer_on(void);
void Buzzer_off(void);
void Buzzer_toggle(void);


#endif
