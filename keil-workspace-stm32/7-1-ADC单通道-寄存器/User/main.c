#include "delay.h"
#include "stdio.h"
#include "adc1.h"

int main()
{
	Driver_ADC1_Init();
	Driver_ADC1_StartConvert();
	
	while(1)
	{
		printf("val = %.4f\r\n", Driver_ADC1_ReadV());
		Delay_ms(1000);
	}
}
