#include "Usart.h"
#include "string.h"
#include "w24c02.h"

int main()
{
	Usart_init();
	//w24c02_init();

	printf("%c\r\n", 'g');
	
//	w24c02_WriteByte(0x00, 'a');
//	w24c02_WriteByte(0x01, 'b');
//	w24c02_WriteByte(0x02, 'c');
//	
//	uint8_t byte1 = w24c02_ReadByte(0x00);
//	uint8_t byte2 = w24c02_ReadByte(0x01);
//	uint8_t byte3 = w24c02_ReadByte(0x02);
//	
//	printf("%c\r\n", byte1);
//	printf("%c\r\n", byte2);
//	printf("%c\r\n", byte3);
	
	
//	w24c02_WriteBytes(0x00, "123456", 6);
//	
//	uint8_t buff[100] = {0};
//	w24c02_ReadBytes(0x00, buff, 6);
//	printf("%s\r\n", buff);
//	
//	
//	memset(buff, 0, sizeof(buff));
//	w24c02_WriteBytes(0x00, "0123456789abcdefghijk", 21);
//	w24c02_ReadBytes(0x00, buff, 21);
//	printf("%s\r\n", buff);
	
	while(1)
	{
		
	}
	
}
