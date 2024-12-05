#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"

uint8_t dataA[] = {0x01, 0x02, 0x03, 0x04};
uint8_t dataB[] = {0, 0, 0, 0};

uint8_t key;

int main()
{
	OLED_Init();
	
	MyDMA_init((uint32_t)dataA, (uint32_t)dataB, 4);
	
	OLED_ShowString(1, 1, "dataA");
	OLED_ShowString(3, 1, "dataB");
	
	OLED_ShowHexNum(1, 8, (uint32_t)dataA, 8);
	OLED_ShowHexNum(3, 8, (uint32_t)dataB, 8);
	
	while(1)
	{
		dataA[0]++;
		dataA[1]++;
		dataA[2]++;
		dataA[3]++;
		
		OLED_ShowHexNum(2, 1, dataA[0], 2);
		OLED_ShowHexNum(2, 4, dataA[1], 2);
		OLED_ShowHexNum(2, 7, dataA[2], 2);
		OLED_ShowHexNum(2, 10, dataA[3], 2);
		
		OLED_ShowHexNum(4, 1, dataB[0], 2);
		OLED_ShowHexNum(4, 4, dataB[1], 2);
		OLED_ShowHexNum(4, 7, dataB[2], 2);
		OLED_ShowHexNum(4, 10, dataB[3], 2);
		
		Delay_ms(1000);
		
		MyDMA_Transfer();
		
		OLED_ShowHexNum(2, 1, dataA[0], 2);
		OLED_ShowHexNum(2, 4, dataA[1], 2);
		OLED_ShowHexNum(2, 7, dataA[2], 2);
		OLED_ShowHexNum(2, 10, dataA[3], 2);
		
		OLED_ShowHexNum(4, 1, dataB[0], 2);
		OLED_ShowHexNum(4, 4, dataB[1], 2);
		OLED_ShowHexNum(4, 7, dataB[2], 2);
		OLED_ShowHexNum(4, 10, dataB[3], 2);
		
		Delay_ms(1000);
	}
}
