#include <REGX52.H>
//#include "Delay.h"
//#include <string.h>

void init_UART()
{
		// 1.设置串口工作模式
		SM0 = 0;
		SM1 = 1;
	
		// 2.设置波特率
		// 2.1 SMOD
		PCON &= 0x7F;
		// 2.2 定时器1
		// 2.2.1 工作模式设置
		TMOD &= 0x0F;
		TMOD |= 0x20;
		// 2.2.2 溢出初始值设置
		// 意思就是过来的时钟频率 在253的基础上，每个时钟频率加1， 达到溢出才产生一次定时
		TL1 = 253;
		TH1 = 253;
		// 2.2.3 启动定时器
		TR1 = 1;
	
		// 3.接收数据相关
		REN = 1; //开启数据接收
		SM2 = 0; //是否检测停止位的有效性（高电平有效） 1:检测，0：不检测	
		
		// 4.串口中断相关配置
		ES = 1;
		EA = 1;
		
		RI = 0;
		TI = 0;
}
// 是否正在发送
static char bit_is_sending = 0;
static char s_buffer = 0;

// 发送一个字符数据
void UART_sendChar(char c)
{
	while(bit_is_sending == 1);
	bit_is_sending = 1;
	SBUF = c;
}

// 发送字符串
void UART_sendStr(char *str)
{
	while(*str != '\0') {
		UART_sendChar(*str);
		str++;
	} 
}

// 验证是否接收数据
bit UART_receiveChar(char *c)
{
	if (s_buffer) {
		*c = s_buffer;
		s_buffer = 0;
		return 1;
	} else {
		return 0;
	}
}


char c;
void main() 
{
	init_UART();
	
	while(1)
	{
		if (UART_receiveChar(&c)) {
			if(c == 'A') {
				P2 = 0x00;
				UART_sendStr("ok: LED is on");
			} else if (c == 'B') {
				P2 = 0xFF;
				UART_sendStr("ok: LED is off");
			} else {
				UART_sendStr("Error: Unknown command");
			}
		}
	}

}


void UART_Routine(void) interrupt 4
{
	if (RI == 1) {
		s_buffer = SBUF;
		
		RI = 0;	//在中断中手动对串口标志位重置
	}
	
	if (TI == 1) {
		bit_is_sending = 0;
		
		TI = 0; //在中断中手动对串口标志位重置
	}
}