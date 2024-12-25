#include "Led.h"

// -------------------------------------------------------------
// 引脚配置层

// SPI写SS引脚电平
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}
// -------------------------------------------------------------

void MySPI_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_InitTypeDef SPI_InitTypeStructure;
	SPI_InitTypeStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitTypeStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitTypeStructure.SPI_CPOL = SPI_CPOL_Low;					// 时钟极性  0： 空闲状态时，SCK保持低电平；  1： 空闲状态时，SCK保持高电平。
	SPI_InitTypeStructure.SPI_CPHA = SPI_CPHA_1Edge;				// 时钟相位 	0： 数据采样从第一个时钟边沿开始；	1： 数据采样从第二个时钟边沿开始。
	SPI_InitTypeStructure.SPI_DataSize = SPI_DataSize_8b; 	// 一次8为传输
	SPI_InitTypeStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// 传输模式- 全双工
	SPI_InitTypeStructure.SPI_FirstBit = SPI_FirstBit_MSB;	// 数据的高位先移动
	SPI_InitTypeStructure.SPI_CRCPolynomial = 7;
	SPI_InitTypeStructure.SPI_NSS = SPI_NSS_Soft;						// NSS 使用软件操作
	SPI_Init(SPI1, &SPI_InitTypeStructure);
	
	SPI_Cmd(SPI1, ENABLE);
	
	MySPI_W_SS(1);					// SS默认高电平
}

// SPI开始
void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

// SPI结束
void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

// SPI交换数据
uint8_t MySPI_SwapByte(uint8_t byteSend)
{	
	while((SPI_I2S_GetFlagStatus(SPI1,SPI_SR_TXE)) != SET);				// 发送缓冲为空  0：发送缓冲非空 1：发送缓冲为空。
	
	SPI_I2S_SendData(SPI1, byteSend);
	
	while((SPI_I2S_GetFlagStatus(SPI1,SPI_SR_RXNE)) != SET);			// 接收缓冲非空  0：接收缓冲为空； 1：接收缓冲非空。
	
	return SPI_I2S_ReceiveData(SPI1);
}






