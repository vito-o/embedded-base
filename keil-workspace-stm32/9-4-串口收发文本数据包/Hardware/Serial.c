#include "Serial.h"

// 发送数据包 包格式：@ xxx \r\n
char Serial_RxPacket[100];	// 定义接收数据包数组， 
uint8_t Serial_RxFlag;			// 定义接收数据包标志位

void Serial_init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitTypeStructure; 
	USART_InitTypeStructure.USART_BaudRate = 9600;																			// 波特率
	USART_InitTypeStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制，不需要
	USART_InitTypeStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;									// 模式，选择为发送和接收模式
	USART_InitTypeStructure.USART_Parity = USART_Parity_No;															// 校验，不需要
	USART_InitTypeStructure.USART_StopBits = USART_StopBits_1;													// 停止位，选择1位
	USART_InitTypeStructure.USART_WordLength = USART_WordLength_8b;											// 字长，8位
	USART_Init(USART1, &USART_InitTypeStructure);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);								// 开启串口接收数据的中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);								// NVIC分组
	
	NVIC_InitTypeDef NVIC_InitTypeStructure;
	NVIC_InitTypeStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitTypeStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitTypeStructure);
	
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
	char str[100];							// 定义字符数组
	va_list arg;								// 定义可变参数列表数据类型的变量arg
	va_start(arg, format);			// 从format开始，接收参数列表到arg变量
	vsprintf(str, format, arg);	// 使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);								// 结束变量arg
	Serial_SendString(str);
}


// USART1中断
void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;								// 定义表示当前状态机状态的静态变量
	static uint8_t pRxPacket = 0;							// 定义表示当前接收数据位置的静态变量
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)	// 判断是否USART1的接收时间触发了中断
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		/*使用状态机的思路，依次处理数据包的不同部分*/
		/*当前状态为0，接收数据包包头*/
		if (RxState == 0)														
		{
			if (RxData == '@' && Serial_RxFlag == 0)										// 如果数据确实是包头
			{
				RxState = 1;
				pRxPacket = 0;
			}
		}
		/*当前状态为1，接收数据包数据*/
		else if (RxState == 1)
		{
			if (RxData == '\r')
			{
				RxState = 2;
			}
			else
			{
				Serial_RxPacket[pRxPacket] = RxData;
				pRxPacket++;
			}
		}
		/*当前状态为2，接收数据包包尾*/
		else if (RxState == 2)
		{
			if (RxData == '\n')										// 如果数据确实是包尾
			{
				RxState = 0;
				Serial_RxPacket[pRxPacket] = '\0';
				Serial_RxFlag = 1;
			}
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		// 清除USART1的RXNE标志位
																											// 读取数据寄存器会自动清除此标志位
																											// 如果已经读取了数据寄存器，也可以不执行此代码
	}
}
