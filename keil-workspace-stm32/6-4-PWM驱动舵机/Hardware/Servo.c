#include "Servo.h"
#include "PWM.h"
#include "OLED.h"

void Servo_init(void)
{
	PWM_init();
}


/*
	angle 范围 0 ~ 180
*/
void Servo_setAngle(float angle)
{
	uint16_t compare = 0;
	
	if (angle < 0) 
	{
		angle = 0;
	}
	
	if (angle > 180) 
	{
		angle = 180;
	}
	
	// 0 ~ 180   0 ~ 2000
	compare = angle * 2000 / 180 + 500 ;
OLED_ShowNum(2, 1, compare, 4);
	// compare 取值范围500~250
	PWM_SetCompare2(compare);
}
