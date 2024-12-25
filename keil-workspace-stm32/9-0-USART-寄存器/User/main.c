#include "Usart.h"
#include "string.h"
#include "delay.h"

int main()
{
	Usart_init();

	Usart1_SendChar('a');
	Usart1_SendChar('B');
	
//	uint8_t ch = Usart1_ReceiveChar();
//	Usart1_SendChar(ch);

	uint8_t *str1 = "Hello atguigu!\r\n";
	Usart1_SendString(str1, strlen((char *)str1));
	
//	uint8_t str[100] = {0};
//	uint8_t len = 0;
//	Usart1_ReceiveString(str, &len);
//	Usart1_SendString(str, len);
	
	while(1)
	{
		
	}
	
}
