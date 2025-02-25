#include "stm32f10x.h"                  // Device header
#include "freertos.h"
#include "task.h"


int main()	
{
	
	while(1)
	{
	
	}
	
}
extern void xPortSysTickHandler(void);
void SysTick_Handler(void)
{
		if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		{
				xPortSysTickHandler();
		}
}
