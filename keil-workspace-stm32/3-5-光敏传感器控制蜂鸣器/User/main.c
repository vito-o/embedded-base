#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint8_t key;

int main()
{
	LightSensor_init();
	Buzzer_init();
	
	while(1)
	{
		key = getLightSensor();
		if (key == 1)
		{
			Buzzer_on();
		}
		else 
		{
			Buzzer_off();
		}
		
	}
}
