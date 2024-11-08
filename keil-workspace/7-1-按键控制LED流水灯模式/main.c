#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char keyNum;
unsigned char LEDMode;

void main() 
{
	P2 = 0xFE;
	Timer0_Init();
	while(1) 
	{
		keyNum = Key();
		if (keyNum)
		{
			if(keyNum==1) {
				LEDMode++;
			} else if (keyNum >= 2) {
				LEDMode = 0;
			}
		}
	}
}


void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	
	TH0 = 64535/256;
	TL0 = 64535%256;
	T0Count++;
	
	if (T0Count >= 500)
	{
		T0Count = 0;
		
		if (LEDMode == 0)
			P2 = _crol_(P2,1);
		if (LEDMode == 1)
			P2 = _cror_(P2,1);
	}
}