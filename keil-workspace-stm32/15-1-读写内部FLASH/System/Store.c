#include "Store.h"
#include "MyFLASH.h"

#define STORE_START_ADDRESS 0x800FC00
#define STORE_COUNT 521

uint16_t Store_Data[STORE_COUNT];

void Store_Init(void)
{
	
	//写入判断这个页是否为自定义数据的标识
	if (MyFLASH_ReadHalfWord(STORE_START_ADDRESS) != 0xA5A5)
	{
		// 擦除整个页
		MyFLASH_ErasePage(STORE_START_ADDRESS);
		// 写入自定义标识
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS, 0xA5A5);
		
		// 将这页除标识数据，其他位置都设置为0
		for (uint16_t i = 1; i < STORE_COUNT; i++)
		{
			MyFLASH_ProgramHalfWord(STORE_START_ADDRESS+i*2, 0x0000);
		}
	}
	
	// 上电时，将闪存数据加载到SRAM中，实现SRAM数据的掉电不丢失
	for (uint16_t i = 0; i < STORE_COUNT; i++)
	{
		Store_Data[i] = MyFLASH_ReadHalfWord(STORE_START_ADDRESS+i*2);
	}
}

void Store_Save(void)
{
	// 擦除整个页
	MyFLASH_ErasePage(STORE_START_ADDRESS);
	for (uint16_t i = 1; i < STORE_COUNT; i++)
	{
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS+i*2, Store_Data[i]);
	}
}

void Store_Clear(void)
{
	for (uint16_t i = 1; i < STORE_COUNT; i++)
	{
		Store_Data[i] = 0x0000;
	}
	Store_Save();
}
