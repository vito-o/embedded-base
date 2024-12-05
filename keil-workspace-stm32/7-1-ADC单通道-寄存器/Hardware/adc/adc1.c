#include "adc1.h"

void Driver_ADC1_Init(void)
{
	// 1.配置时钟
	// 1.1 ADC1时钟配置
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	// 1.2 配置ADC1时钟分频12MHZ	
	RCC->CFGR |= RCC_CFGR_ADCPRE_1;
	RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;
	
	// 1.3 配置GPIO的时钟
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// 2. 配置gpio工作模式：PC0模拟输入， CNF=00 MODE= 00
	GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	
	// 3. 配置adc相关
	// 3.1 禁止扫描，只有一个通道不用扫描
	ADC1->CR1 &= ~ADC_CR1_SCAN;
	// 3.2 启用连续转换模式， CR2 = CONT 1 ,
	ADC1->CR2 |= ADC_CR2_CONT;
	// 3.3 数据的对齐方式
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	// 3.4 设置通道0的采样时间 ADC_SMPR2 
	ADC1->SMPR2 |= ADC_SMPR2_SMP0_2;
	ADC1->SMPR2 &= ~ADC_SMPR2_SMP0_1;
	ADC1->SMPR2 |= ADC_SMPR2_SMP0_0;
	// 3.5 通道组配置
	// 3.5.1 配置几个通道需要转换,配置规则通道序列长度
	ADC1->SQR1 &= ~ADC_SQR1_L;
	// 3.5.2 把通道号配置到组里
	ADC1->SQR3 &= ~ADC_SQR3_SQ1;
	ADC1->SQR3 |= 0 << 0; // 将SQR3的最后5位设置为0
	
	// 3.6 选择软件触发
	ADC1->CR2 |= ADC_CR2_EXTTRIG; // 使用规则组外部转换
	ADC1->CR2 |= ADC_CR2_EXTSEL;	// 使用	软件触发adc					
	
}

void Driver_ADC1_StartConvert(void)
{
	// 1.上电，把adc从休眠模式唤醒，
	ADC1->CR2 |= ADC_CR2_ADON;
	
	// 2.执行校准
	ADC1->CR2 |= ADC_CR2_CAL;
	while(ADC1->CR2 & ADC_CR2_CAL);
	
	// 3.使用软件开始转换规则通道
	ADC1->CR2 |= ADC_CR2_SWSTART;
	
	// 4.等待首次完成转换
	while((ADC1->SR & ADC_SR_EOC) == 0);
}

double Driver_ADC1_ReadV(void)	
{
	// 12位的ADC范围[0-4095]
	return ADC1->DR * 3.3 / 4095;
}
