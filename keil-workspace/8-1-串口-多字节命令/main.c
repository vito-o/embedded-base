#include <REGX52.H>
#include <Timer0.h>
//#include "Delay.h"
#include <string.h>

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
static unsigned char bit_is_sending = 0;
// 接收数据变量
static unsigned char s_buffer[16] = {0};
static unsigned char s_index = 0;

static unsigned char s_is_complete = 0;
static unsigned char s_time_count = 0;


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
bit UART_receiveStr(char *str)
{
	unsigned char i;
	
	if (s_is_complete) {
		for(i = 0; i < s_index; i++) {
			str[i] = s_buffer[i];
		}
		str[i] = '\0';
		s_index = 0;
		s_is_complete = 0;
		
		return 1;
	} else {
		return 0;
	}
}

char command[16] = {0};
void main() 
{
	Timer0_Init();
	init_UART();
	
	while(1)
	{
		if (UART_receiveStr(command)) {
			if(strcmp(command, "on") == 0) {
				P2 = 0x00;
				UART_sendStr("ok: LED is on");
			} else if (strcmp(command, "off") == 0) {
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
		//s_buffer = SBUF;
		s_buffer[s_index++] = SBUF;
		s_time_count = 0; //定时器，每次接收到数据后，s_time_count重置
		RI = 0;	//在中断中手动对串口标志位重置
	}
	
	if (TI == 1) {
		bit_is_sending = 0;
		
		TI = 0; //在中断中手动对串口标志位重置
	}
}

// 定时器
void Timer0_Routine() interrupt 1
{
	TH0 = 64535/256;
	TL0 = 64535%256;
	s_time_count++;
	
	if (s_index > 0 && s_time_count >= 10) {
		s_is_complete = 1;
		s_time_count = 0;
	}
}