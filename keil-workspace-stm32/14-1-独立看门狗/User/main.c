#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint8_t key;

// 看门狗会复位电路，让代码重新执行

int main()
{
	OLED_Init();
	Key_init();
	
	OLED_ShowString(1, 1, "IWDG TEST");
	
	// 判断复位信号来源
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET) // 如果是独立看门狗
	{
		OLED_ShowString(2, 1, "IWDGRST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		RCC_ClearFlag();	// 清除标志位
	}
	else
	{
		OLED_ShowString(3, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(3, 1, "   ");
		Delay_ms(100);
	}
	
	// IWDG初始化
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // 独立看门狗写使能（这样可以向寄存器里面写入数据）
	IWDG_SetPrescaler(IWDG_Prescaler_16);					// 设置预分频为16
	IWDG_SetReload(2500-1);												// 设置重装值为2500-1，独立看门狗的超时时间为1000ms
	IWDG_ReloadCounter();													// 重装计数器，喂狗
	IWDG_Enable();																// 独立看门狗使能
	
	while(1)
	{
		getKey();									// 调用阻塞式的按键扫描函数，模拟主循环卡死
		
		IWDG_ReloadCounter();			// 重装计数器，喂狗
		
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(200);
		OLED_ShowString(4, 1, "    ");
		Delay_ms(600);
	}
}
