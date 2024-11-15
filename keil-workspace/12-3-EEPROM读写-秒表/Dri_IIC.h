#ifndef __DIR_IIC_H__
#define __DIR_IIC_H__

void Dir_IIC_Start();
void Dir_IIC_SendByte(unsigned char byte);
unsigned char Dri_IIC_ReceiveAck();
unsigned char Dir_IIC_ReceiveByte();
void Dir_IIC_SendAck(unsigned char ack);
void Dir_IIC_Stop();

#endif