#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Driver_DMA.h"

const uint8_t src[] = {10, 20, 30, 40};
uint8_t des[4] = {0};

uint8_t key;

int main()
{
	OLED_Init();
	Driver_DMA1_init();
	
	Driver_DMA1_TransmitData((uint32_t)&src[0], (uint32_t)&des[0], 4);
	
	while(isTransmitFinished == 0);
	
	OLED_ShowNum(1,1, des[0], 2);
	OLED_ShowNum(1,4, des[1], 2);
	OLED_ShowNum(1,7, des[2], 2);
	OLED_ShowNum(1,10, des[3], 2);
	
	while(1)
	{
		
	}
}
