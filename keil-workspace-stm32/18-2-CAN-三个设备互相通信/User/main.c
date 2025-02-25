#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "MyCAN.h"

uint8_t key;

uint32_t TxID = 0x777;
uint8_t TxLength = 4;
uint8_t TxData[] = {0x11, 0x22, 0x33, 0x44};

uint32_t RxID;
uint8_t RxLength;
uint8_t RxData[8];

int main()
{
	OLED_Init();
	Key_init();
	MyCAN_Init();
	
	OLED_ShowString(1, 1, "TxID:");
	OLED_ShowHexNum(1, 6, TxID, 3);
	OLED_ShowString(2, 1, "RxID:");
	OLED_ShowString(3, 1, "Leng:");
	OLED_ShowString(4, 1, "Data:");
	
	while(1)
	{
		key = getKey();
		if (key == 1)
		{
			TxData[0]++;
			TxData[1]++;
			TxData[2]++;
			TxData[3]++;
			// 发送
			MyCAN_Transmit(TxID, TxLength, TxData);
		}
		
		// 判断是否接收到数据
		if (MyCAN_ReceiveFlag())
		{
			MyCAN_Receive(&RxID, &RxLength, RxData);
			
			OLED_ShowHexNum(2, 6, RxID, 3);
			OLED_ShowHexNum(3, 6, RxLength, 1);
			for(uint8_t i = 0; i < RxLength; i++)
			{
				OLED_ShowHexNum(4, i*3 + 6, RxData[i], 2);
			}
		}
	}
}
