#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Motor.h"
#include "Delay.h"
#include "Key.h"

uint16_t key;
int8_t speed;


int main()
{
	OLED_Init();
	Motor_init();
	Key_init();

	OLED_ShowString(1, 3, "num:");
	
	while(1)
	{
		key = getKey();
		
		if (key == 1)
		{
			speed += 20;
			if (speed > 100)
			{
				speed = -100;
			}
			Motor_SetSpeed(speed);
		}
		OLED_ShowNum(1, 7, speed, 3);
	}
}

