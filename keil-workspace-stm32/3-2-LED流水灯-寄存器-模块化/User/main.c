#include "delay.h"
#include "led.h"

int main()
{

	Led_init();

	uint16_t Leds[] = { Led1, Led2, Led3 };
	uint8_t n =3;

	// 往复流水灯
	while(1)
	{
		for (uint8_t i = 0; i < n; i++)
		{
			Led_on(Leds[i]);	// 开灯
			Delay_ms(500);
			Led_off(Leds[i]);
		}
		for (uint8_t i = n-2; i > 0; i--)
		{
			Led_on(Leds[i]);	// 开灯
			Delay_ms(500);
			Led_off(Leds[i]);
		}
	}
	
}
