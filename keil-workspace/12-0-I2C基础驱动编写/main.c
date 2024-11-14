#include <REGX52.H>

void Dir_IIC_Start()
{
	//初始 将两个信号拉高
	SCL = 1;
	SDA = 1;
	//当将SDA拉低后，发送起始信号
	SDA = 0;
	
	//这里将scl又拉低，以便准备接下来要发送数据位（因为scl拉高后就开始读取数据）
	SCL = 0;
}

// 发送数据
void Dir_IIC_SendByte(unsigned char byte)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		SDA = (byte & (0x80 >> i)) == 0 ? 0 : 1; //填充数据
		SCL = 1; //拉高发送数据
		SCL = 0; //拉低准备下一个数据
	}
}

// 接收确认
unsigned char Dri_IIC_ReceiveAck()
{
	unsigned char ack;
	
	// 释放SDA，以便从设备从SDA发送数据
	SDA = 1;
	
	// 拉高SCL以便读取从设备发送的数据
	SCL = 1;
	ack = SDA; //读取数据
	
	//拉低准备下一个数据
	SCL = 0;
	
	return ack;
}

// 接收数据
unsigned char Dir_IIC_ReceiveByte()
{
	unsigned char byte = 0;
	unsigned char i;
	
	// 释放SDA，以便从设备从SDA发送数据
	SDA = 1;
	for (i = 0; i < 8; i++)
	{
		//拉高读数据
		SCL = 1; 
		byte = (byte << 1) | SDA;
		//拉低准备下一个数据
		SCL = 0;
	}
	return byte;
}

// 发送确认
void Dir_IIC_SendAck(unsigned char ack)
{
	//塞入确认信号
	SDA = ack;
	//拉高读数据
	SCL = 1;
	//拉低准备下一个数据
	SCL = 0;
}

// 结束信号
void Dir_IIC_Stop()
{
	// 当前操作之前，SCL为低，SDA未知
	// 因为结束信号是两个信号都拉高，但是他们拉高是有顺序的(SCL先SDA拉高)，所以先
	SDA = 0; 
	SCL = 1;
	SDA = 1;
}

void main() 
{

	while(1) 
	{
		
	}
}