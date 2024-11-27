#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Encoder.h"

int16_t count;

int main()
{
	OLED_Init();
	Encoder_init();
	
	OLED_ShowString(1, 3, "num:");

	while(1)
	{
		count += Envoder_Get();
		OLED_ShowNum(2, 1, count, 5);
	}
}
