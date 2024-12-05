#include "Driver_DMA.h"

void Driver_DMA1_init(void)
{
	// 1.开启时钟
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	// 2.DMA相关配置
	// 2.1 DMA方向： 从存储器ROM到存储器RAM，
	DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;			//数据传输方向
	DMA1_Channel1->CCR |= DMA_CCR1_MEM2MEM;		// 是否为存储器到存储器模式
	
	// 2.2 设置存储器和外设的数据宽度
	DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE;
	DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE;
	
	// 2.3 设置外设和存储器的地址是否自增
	DMA1_Channel1->CCR |= DMA_CCR1_PINC;
	DMA1_Channel1->CCR |= DMA_CCR1_MINC;
	
	// 2.4 开启传输完成的中断
	DMA1_Channel1->CCR |= DMA_CCR1_TCIE;
	
	// 2.5 NVIC配置
	NVIC_SetPriorityGrouping(3);
	NVIC_SetPriority(DMA1_Channel1_IRQn, 3);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

void Driver_DMA1_TransmitData(uint32_t srcAddr, uint32_t desAddr, uint16_t dataLen)
{
	// 1. 设置外设地址
	DMA1_Channel1->CPAR = srcAddr;
	
	// 2.设置存储器地址
	DMA1_Channel1->CMAR = desAddr;
	
	// 3.设置要传输的数据量
	DMA1_Channel1->CNDTR = dataLen;
	
	// 4.开启通道，开始传输
	DMA1_Channel1->CCR |= DMA_CCR1_EN;
}

uint8_t isTransmitFinished;

void DMA1_Channel1_IRQHandler(void)
{
	if (DMA1->ISR & DMA_ISR_TCIF1)
	{
		// 清除传输完成中断标志位
		DMA1->IFCR |= DMA_IFCR_CGIF1;
		
		// 通道不需要，可以关闭
		DMA1_Channel1->CCR &= ~DMA_CCR1_EN;
		
		isTransmitFinished = 1;
	}

}
