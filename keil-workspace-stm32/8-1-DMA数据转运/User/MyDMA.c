#include "MyDMA.h"

uint16_t DMA_size;

void MyDMA_init(uint32_t dataA, uint32_t dataB, uint16_t size)
{
	DMA_size = size;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);											// 开启时钟										
	
	DMA_InitTypeDef DMA_InitTypeStructure;		
	DMA_InitTypeStructure.DMA_PeripheralBaseAddr = dataA;										// 外设基地址
	DMA_InitTypeStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	// 外设数据宽度，选择字节
	DMA_InitTypeStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;					// 外设地址自增，选择使能
	DMA_InitTypeStructure.DMA_MemoryBaseAddr = dataB;												// 存储器基地址
	DMA_InitTypeStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			// 存储器数据宽度，选择字节
	DMA_InitTypeStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;							// 存储器地址自增
	DMA_InitTypeStructure.DMA_Mode = DMA_Mode_Normal;												// 模式，选择正常模式
	DMA_InitTypeStructure.DMA_BufferSize = DMA_size;												// 运转的数据大小（转运次数）
	DMA_InitTypeStructure.DMA_DIR = DMA_DIR_PeripheralSRC;									// 数据转运方向，选择由外设到存储器
	DMA_InitTypeStructure.DMA_M2M = DMA_M2M_Enable;													// 存储器到存储器，使能（选择硬件或其他控制使能）
	DMA_InitTypeStructure.DMA_Priority = DMA_Priority_Medium;								// 优先级
	
	DMA_Init(DMA1_Channel1, &DMA_InitTypeStructure);
	
	DMA_Cmd(DMA1_Channel1, DISABLE);																					// 这里先不给使能，初始化后不立即工作，灯后续调用Transfer后，再开始
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);	 								// DMA失能，再写入传输数据之前，需要DMA暂停工作
	DMA_SetCurrDataCounter(DMA1_Channel1, DMA_size);
	DMA_Cmd(DMA1_Channel1, ENABLE);										// DMA使能，开始工作
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); // 等待DMA完成工作
	DMA_ClearFlag(DMA1_FLAG_TC1);											// DMA完成工作标记位
}
