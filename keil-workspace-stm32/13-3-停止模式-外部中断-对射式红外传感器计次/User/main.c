#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "CountSensor.h"
#include "Delay.h"

int main()
{
	OLED_Init();
	CountSensor_init();

	// 开启PWR的时钟
	// 停止模式和待机模式一定要开启
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	OLED_ShowString(1, 1, "Count:");
	
	while(1)
	{
		OLED_ShowNum(1, 7, CountSensor_Get(), 5);
		
		
		OLED_ShowString(2, 3, "Running");
		Delay_ms(100);
		OLED_ShowString(2, 3, "       ");
		Delay_ms(100);
		
		// stm32进入停机模式，并等待中断唤醒
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		// 唤醒后，要重新设置时钟
		SystemInit();
	}
}
