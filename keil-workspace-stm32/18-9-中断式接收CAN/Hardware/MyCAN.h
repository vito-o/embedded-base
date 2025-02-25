#ifndef __MyCAN_H
#define __MyCAN_H

#include "stm32f10x.h" 

void MyCAN_Init(void);

// 发送
void MyCAN_Transmit(CanTxMsg *TxMessage);

// 判断是否接收
uint8_t MyCAN_ReceiveFlag(void);

void MyCAN_Receive(CanRxMsg *RxMessage);

extern CanRxMsg MyCAN_RxMsg;
extern uint8_t MyCAN_RxFlag;

#endif
