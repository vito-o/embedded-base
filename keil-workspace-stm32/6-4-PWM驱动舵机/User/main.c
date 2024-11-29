#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Servo.h"
#include "Delay.h"
#include "Key.h"

uint16_t key;
float angle;


int main()
{
	OLED_Init();
	Servo_init();
	Key_init();

	OLED_ShowString(1, 3, "num:");
	
	while(1)
	{
		key = getKey();
		if (key == 1)
		{
			angle += 30;
			if (angle > 180)
			{
				angle = 0;
			}
		}
		
		Servo_setAngle(angle);

		OLED_ShowNum(1, 7, angle, 3);
		
	}
}

