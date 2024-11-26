#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"

uint8_t key;

int main()
{
	Led_init();
	Key_init();
	
	while(1)
	{
		key = getKey();
		if (key == 1)
		{
			Led1_on();
		}
		if (key == 2)
		{
			Led1_off();
		}
	}
}
