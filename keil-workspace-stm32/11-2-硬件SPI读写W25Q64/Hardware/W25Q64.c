#include "W25Q64.h"

void W25Q64_init(void)
{
	MySPI_init();
}


void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID <<= 8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	
	MySPI_Stop();
}

void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

void W25Q64_WaitBusy(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1); 		// 发送读状态计算器1的指令
	uint32_t timeout = 100000;
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)	// 循环等待忙标志位
	{
		timeout--;
		if (timeout == 0)
		{
			break;
		}
	}
	MySPI_Stop();
}

// 页编程， 向页内写入，超出一页则从页头重复写入
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	W25Q64_WriteEnable();  					// 开启写使能
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address >> 16);	// 交换发送地址23~16
	MySPI_SwapByte(Address >> 8);		// 交换发送地址15~8
	MySPI_SwapByte(Address);				// 交换发送地址7~0
	
	for(uint16_t i = 0; i < Count; i++)
	{
		MySPI_SwapByte(DataArray[i]);
	}
	
	MySPI_Stop();
	
	W25Q64_WaitBusy();							// 等待模块忙的结束
}

// 擦除扇区（4KB）
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();  					// 开启写使能
	
	MySPI_Start();
	
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Address >> 16);	// 交换发送地址23~16
	MySPI_SwapByte(Address >> 8);		// 交换发送地址15~8
	MySPI_SwapByte(Address);				// 交换发送地址7~0
	MySPI_Stop();
	
	W25Q64_WaitBusy();							// 等待模块忙的结束
}

// 读取数据
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	MySPI_Start();
	
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address >> 16);	// 交换发送地址23~16
	MySPI_SwapByte(Address >> 8);		// 交换发送地址15~8
	MySPI_SwapByte(Address);				// 交换发送地址7~0
	
	for(uint32_t i = 0; i < Count; i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	
	MySPI_Stop();
}
