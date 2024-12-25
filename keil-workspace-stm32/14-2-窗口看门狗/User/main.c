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
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET) // 如果是窗口看门狗
	{
		OLED_ShowString(2, 1, "WWDGRST");
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
	
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	// WWDG初始化
	WWDG_SetPrescaler(WWDG_Prescaler_8);	// 设置预分频系数为8
	WWDG_SetWindowValue(0x40 | 21);				// 设置窗口值，窗口时间为30ms
	WWDG_Enable(0x40 | 54);								// 使能并第一次喂狗，超时时间为50ms
	
	while(1)
	{
		getKey();												// 调用阻塞式的按键扫描函数，模拟主循环卡死
		
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(20);
		OLED_ShowString(4, 1, "    ");
		Delay_ms(20);
		
		WWDG_SetCounter(0x40 | 54);			// 重装计数器，喂狗(这里和第一次喂狗时间不能太短，因为回到值小于30ms时间从而产生复位)
	}
}
