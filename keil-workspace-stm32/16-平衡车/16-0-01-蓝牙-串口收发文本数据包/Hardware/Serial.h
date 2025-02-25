#ifndef __Serial_H
#define __Serial_H

#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

extern char Serial_RxPacket[100];
extern uint8_t Serial_RxFlag;

void Serial_init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendArray(uint8_t *array, uint16_t length);
void Serial_SendString(char *str)	;
uint32_t Serial_Pow(uint32_t x, uint32_t y);
void Serial_SendNumber(uint32_t Num, uint8_t len);
void Serial_Printf(char *format, ...);
void clear_RxPacket(void);

#endif

