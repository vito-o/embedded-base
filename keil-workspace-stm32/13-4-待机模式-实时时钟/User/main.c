#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

uint8_t key;

int main()
{
	OLED_Init();
	MyRTC_init();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	OLED_ShowString(1, 1, "CNT :");
	OLED_ShowString(2, 1, "ALR :");
	OLED_ShowString(3, 1, "ALRF:");
	
	// 设定闹钟
	uint32_t alarm = RTC_GetCounter() + 5;
	RTC_SetAlarm(alarm);
	OLED_ShowNum(2, 6, alarm, 10);
	
	while(1)
	{
		OLED_ShowNum(1, 6, RTC_GetCounter(), 10);	 //显示32位的秒计数器
		OLED_ShowNum(3, 6, RTC_GetFlagStatus(RTC_FLAG_ALR), 1);	 //显示闹钟标志位
		
		OLED_ShowString(4, 1, "Running");			//OLED闪烁Running，指示当前主循环正在运行
		Delay_ms(100);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(100);
		
		OLED_ShowString(4, 9, "STANDBY");			//OLED闪烁STANDBY，指示即将进入待机模式
		Delay_ms(1000);
		OLED_ShowString(4, 9, "       ");
		Delay_ms(100);
		
		OLED_Clear();													//OLED清屏，模拟关闭外部所有的耗电设备，以达到极度省电
		
		PWR_EnterSTANDBYMode();								// STM32进入停止模式，并等待指定的唤醒事件（WKUP上升沿或RTC闹钟）
		// 待机模式唤醒后，程序会重头开始运行
	}
}
