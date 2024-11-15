#include "Dri_IIC.h"
#include "Delay.h"

#define DEV_ADDR 0xA0
#define PAGE_SIZE 16

unsigned char Int_EEPROM_WritePage(unsigned char addr, unsigned char *bytes, unsigned char len)
{
	unsigned char ack = 0;
	unsigned char i;
	
	//发送起始信号
	Dir_IIC_Start();
	
	//发送设备地址
	Dir_IIC_SendByte(DEV_ADDR);
	ack |= Dri_IIC_ReceiveAck();
	
	//发送字地址
	Dir_IIC_SendByte(addr);
	ack |= Dri_IIC_ReceiveAck();
	
	for(i = 0; i < len; i++) {
		Dir_IIC_SendByte(bytes[i]);
		ack |= Dri_IIC_ReceiveAck();
	}
	
	//发送结束信号
	Dir_IIC_Stop();
	
	//等待EEPROM内部写入完成
	Delay(5);
	
	return ack;
}

unsigned char Int_EEPROM_WriteBytes(unsigned char addr, unsigned char *bytes, unsigned char len)
{
	//当前页剩余空间
	unsigned char page_remain;
	unsigned char ack = 0;
	
	while(len > 0) {
		page_remain = PAGE_SIZE - (addr % PAGE_SIZE);
		if (len > page_remain) {
			// 当前页面空间不足，先写满当前页
			ack |= Int_EEPROM_WritePage(addr, bytes, page_remain);
			// 剩余内容写到下一页
			len -= page_remain;
			bytes += page_remain;
			addr += page_remain;
			
		} else {
			// 当页面空间足够，直接写入剩余内容
			ack |= Int_EEPROM_WritePage(addr, bytes, len);
			len = 0;
		}
	}
}


unsigned char Int_EEPROM_ReadBytes(unsigned char addr, unsigned char *bytes, unsigned char len)
{
	unsigned char ack = 0;
	unsigned char i;
	
	//发送起始信号
	Dir_IIC_Start();
	
	//发送设备地址
	Dir_IIC_SendByte(DEV_ADDR);
	ack |= Dri_IIC_ReceiveAck();
	
	//发送字地址
	Dir_IIC_SendByte(addr);
	ack |= Dri_IIC_ReceiveAck();
	
	//再次发送起始信号
	Dir_IIC_Start();
	//发送设备地址
	Dir_IIC_SendByte(DEV_ADDR+1);
	ack |= Dri_IIC_ReceiveAck();
	//读取数据
	for (i = 0; i < len; i++) {
		bytes[i] = Dir_IIC_ReceiveByte();
		Dir_IIC_SendAck(i==len-1 ? 1:0);
	}
	//发送结束信号
	Dir_IIC_Stop();
	
	return ack;
}