#ifndef __MYRTC_H
#define __MYRTC_H

#include "stm32f10x.h"                  // Device header

extern uint16_t MyRTC_Time[];

void MyRTC_init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);


#endif
