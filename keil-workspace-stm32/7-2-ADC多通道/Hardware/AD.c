#include "AD.h"
// 模拟ADC数据输入，
void AD_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 设置ADC时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);							// 选择时钟6分频，ADCCLK = 72MHZ / 6 = 12MHZ
	

	// ADC初始化
	ADC_InitTypeDef ADC_InitTypeStructure;
	ADC_InitTypeStructure.ADC_ContinuousConvMode = DISABLE;									// 设置是否连续转换，每转换一次规则组序列后停止
	ADC_InitTypeStructure.ADC_DataAlign = ADC_DataAlign_Right;							// 数据对齐，右对齐
	ADC_InitTypeStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 设置外部触发源。这里使用 ADC_ExternalTrigConv_None，意味着 ADC 转换由软件触发，而不是外部信号触发。
	ADC_InitTypeStructure.ADC_Mode = ADC_Mode_Independent;									// 表示 ADC1 在独立模式下工作，即不与其他 ADC 共享资源。如果使用双 ADC 模式，则可以设置为 ADC_Mode_RegInjecSimult 等。
	ADC_InitTypeStructure.ADC_NbrOfChannel = 1;															// 通道数，为1，仅再扫描模式下，才需要指定大于1的数，在非扫描模式下，只能是1
	ADC_InitTypeStructure.ADC_ScanConvMode = DISABLE;												// 扫描模式，失能，只转换规则组的序列1这一个位置
	ADC_Init(ADC1, &ADC_InitTypeStructure);
	
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
	
}

// 获取adc的值
uint16_t AD_GetValue(uint8_t ADC_Channel)	
{
	// 规则通道配置
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5); // 规则组序列1的位置，配置为通道0
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);																	// 软件触发ADC转换1次
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);									// 等待EOC标志位，即等待AD转换结果
	return ADC_GetConversionValue(ADC1);																		// 读数据寄存器，得到AD转换的结果
}
