#include "AD.h"

uint16_t AD_Value[4];

// 模拟ADC数据输入，
void AD_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);											// 开启DMA1时钟

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 设置ADC时钟分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);							// 选择时钟6分频，ADCCLK = 72MHZ / 6 = 12MHZ
	
	// 规则通道配置
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // 规则组序列1的位置，配置为通道0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5); // 规则组序列2的位置，配置为通道1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5); // 规则组序列3的位置，配置为通道2
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5); // 规则组序列4的位置，配置为通道3
	
	// ADC初始化
	ADC_InitTypeDef ADC_InitTypeStructure;
	ADC_InitTypeStructure.ADC_ContinuousConvMode = ENABLE;									// 设置是否连续转换，每转换一次规则组序列后立刻开始下一次转换
	ADC_InitTypeStructure.ADC_DataAlign = ADC_DataAlign_Right;							// 数据对齐，右对齐
	ADC_InitTypeStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 设置外部触发源。这里使用 ADC_ExternalTrigConv_None，意味着 ADC 转换由软件触发，而不是外部信号触发。
	ADC_InitTypeStructure.ADC_Mode = ADC_Mode_Independent;									// 表示 ADC1 在独立模式下工作，即不与其他 ADC 共享资源。如果使用双 ADC 模式，则可以设置为 ADC_Mode_RegInjecSimult 等。
	ADC_InitTypeStructure.ADC_NbrOfChannel = 4;															// 通道数，为4，仅再扫描模式下，才需要指定大于1的数，在非扫描模式下，只能是1
	ADC_InitTypeStructure.ADC_ScanConvMode = ENABLE;												// 扫描模式，使能，扫描规则组的序列，扫描量由ADC_NbrOfChannel确定
	ADC_Init(ADC1, &ADC_InitTypeStructure);
	
	// DMA初始化
	DMA_InitTypeDef DMA_InitTypeStructure;		
	DMA_InitTypeStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;							// 外设基地址
	DMA_InitTypeStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// 外设数据宽度，选择字节
	DMA_InitTypeStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;								// 外设地址不自增
	DMA_InitTypeStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;									// 存储器基地址
	DMA_InitTypeStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;					// 存储器数据宽度，选择字节
	DMA_InitTypeStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;											// 存储器地址自增
	DMA_InitTypeStructure.DMA_Mode = DMA_Mode_Circular;															// 循环模式，与adc的连续转换一致
	DMA_InitTypeStructure.DMA_BufferSize = 4;																				// 运转的数据大小（转运次数）
	DMA_InitTypeStructure.DMA_DIR = DMA_DIR_PeripheralSRC;													// 数据转运方向，选择由外设到存储器
	DMA_InitTypeStructure.DMA_M2M = DMA_M2M_Disable;																// 存储器到存储器，失能（选择硬件或其他控制使能）
	DMA_InitTypeStructure.DMA_Priority = DMA_Priority_Medium;												// 优先级
	DMA_Init(DMA1_Channel1, &DMA_InitTypeStructure);
	
	// DMA使能
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);					// ADC1触发DMA1的信号使能
	// ADC使能
	ADC_Cmd(ADC1, ENABLE);
	
	// ADC校准
	// 重置 ADC 校准过程。这是一个硬件相关的步骤，会启动校准过程，并将 ADC 内部寄存器恢复到初始状态。
	ADC_ResetCalibration(ADC1);																							// 固定流程，内部有电路会自动执行校准
	// 检查 ADC 是否完成了重置校准。这个 while 循环会一直等待，直到校准重置完成。
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	// 启动 ADC 的校准过程。校准过程可以提高 ADC 的精度。
	ADC_StartCalibration(ADC1);
	// 检查 ADC 是否完成了校准。这个 while 循环会一直等待，直到校准完成。
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);																	// 软件触发ADC转换1次，由于adc处于连续转换模式，故触发一次后ADC就可以一直工作
}
