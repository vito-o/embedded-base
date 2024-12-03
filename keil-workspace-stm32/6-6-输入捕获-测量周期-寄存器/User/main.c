#include "delay.h"
#include "time2.h"
#include "time3.h"
#include "stdio.h"
uint8_t i;

int main()
{
	TIME2_init();
	TIME2_Start();
	
	TIME3_init();
	TIME3_Start();
	
	double t, f;
	while(1)
	{
		t = TIME3_GetPWMCycle();
		f = TIME3_GetPWMFreq();
		
		printf("t = %.4fms, f = %.4fHz\r\n", t, f);
		Delay_ms(1000);
	}
}
