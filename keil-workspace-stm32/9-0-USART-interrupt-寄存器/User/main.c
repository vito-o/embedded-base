#include "Usart.h"
#include "string.h"

int main()
{
	Usart_init();

	//Usart1_SendChar('a');
	//Usart1_SendChar('\n');

	uint8_t *str1 = "Hello atguigu!\r\n";
	Usart1_SendString(str1, strlen((char *)str1));
	
	
	while(1)
	{
		if (isToSend)
		{
			Usart1_SendString(buff, len);
			isToSend = 0;
			len = 0;
		}
	}
	
}
