#include "Serial.h"

void Serial_init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitTypeStructure; 
	USART_InitTypeStructure.USART_BaudRate = 9600;																			// 波特率
	USART_InitTypeStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制，不需要
	USART_InitTypeStructure.USART_Mode = USART_Mode_Tx;																	// 模式，选择为发送模式
	USART_InitTypeStructure.USART_Parity = USART_Parity_No;															// 校验，不需要
	USART_InitTypeStructure.USART_StopBits = USART_StopBits_1;													// 停止位，选择1位
	USART_InitTypeStructure.USART_WordLength = USART_WordLength_8b;											// 字长，8位
	USART_Init(USART1, &USART_InitTypeStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t byte)
{
	USART_SendData(USART1, byte);		// 将字节数据写入数据寄存器，写入后usart自动生成时序波形
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	// 等待发送完成
	//下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位
}

void Serial_SendArray(uint8_t *array, uint16_t length)
{
	uint16_t i;
	for(i = 0; i < length; i++)
	{
		Serial_SendByte(array[i]);
	}
}

void Serial_SendString(char *str)
{
	uint16_t i;
	for(i = 0; str[i] != '\0'; i++)
	{
		Serial_SendByte(str[i]);
	}
}

uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
	uint32_t Result = 1;
	while(y--)
	{
		Result *= x;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Num, uint8_t len)
{
	uint8_t i;
	for(i = 0; i < len; i++)
	{
		Serial_SendByte(Num / Serial_Pow(10, len-i-1) % 10 + '0');
	}
}

/*
	使用printf需要重定向底层函数

*/
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

/*
	字节封装的print函数
	参数：format 格式化字符串
	参数：... 可变的参数列表
 */
void Serial_Printf(char *format, ...)
{
	char String[100];				//定义字符数组
	va_list arg;					//定义可变参数列表数据类型的变量arg
	va_start(arg, format);			//从format开始，接收参数列表到arg变量
	vsprintf(String, format, arg);	//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);					//结束变量arg
	Serial_SendString(String);		//串口发送字符数组（字符串）
}

