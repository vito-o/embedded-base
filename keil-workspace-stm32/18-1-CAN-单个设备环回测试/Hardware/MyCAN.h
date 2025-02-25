#ifndef __MyCAN_H
#define __MyCAN_H

#include "stm32f10x.h" 

void MyCAN_Init(void);

// 发送
void MyCAN_Transmit(uint32_t ID, uint8_t Length, uint8_t *Data);

// 判断是否接收
uint8_t MyCAN_ReceiveFlag(void);

void MyCAN_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data);



#endif
