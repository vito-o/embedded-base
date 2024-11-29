
#include "led.h"
#include "Systick.h"

int main()
{

	Led_init();
	SysTick_init();

	// 往复流水灯
	while(1)
	{
		
	}
	
}
