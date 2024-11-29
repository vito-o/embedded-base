#include "CountSensor.h"

uint16_t CountSensor_count;

// 通过B14引脚-输入 对射式红外传感器信号
void CountSensor_init(void)
{
	// 引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// AFIO  开启AFIO的时钟，外部中断必须开启AFIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// AFIO选择中断引脚
	// 将外部中断的14号线映射到GPIOB，即选择PB14为外部中断引脚
	// 因为 GPIO (A~G) 中的相同引脚（0~15） 在exti中使用同一个线映射，所以这里将GPIOB 映射到14号线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	// EXTI初始化
	// 外交部 - 选择要处理哪个线的中断
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;							// 选择配置外部中断的14号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;								// 指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			// 指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	// 指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	// NVIC中断分组
	// 配置NVIC为分组
	// 即抢占优先级范围：0~3，响应优先级为：0~3
	// 此分组配置在整个工程中仅需调用一次
	// 若有多个中断，可以把此代码放在main函数内，while循环之前
	// 若调用多次配置分组的代码，则后执行的配置回覆盖先执行的配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				
	
	// NVIC配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;							// 选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;										// 指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;					// 指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;								// 指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);																		// 配置NVIC外设
}

uint16_t CountSensor_Get()
{
	return CountSensor_count;
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)			// 判断是否是外部中断14号线触发的中断
	{
		// 如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_count ++;
		}
		
		// 清除外部中断14号线的中断标志位
		// 中断标志位必须清除
		// 否则中断将连续不断的触发，导致主程序卡死
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
