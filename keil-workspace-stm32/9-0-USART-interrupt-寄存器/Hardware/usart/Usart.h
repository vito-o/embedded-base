#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"    

void Usart_init(void);

void Usart1_SendChar(uint8_t byte);
uint8_t Usart1_ReceiveChar(void);
void Usart1_SendString(uint8_t *str, uint16_t len);
void Usart1_ReceiveString(uint8_t buff[], uint8_t *len);

extern uint8_t buff[100];
extern uint8_t len;
extern uint8_t isToSend;

#endif
