#include <REGX52.H>
#include "Key.h"
#include "Nixie.h"
#include "Buzzer.h"

unsigned char keyNum;

void main()
{
	Nixie(1, 0);
	while(1)
	{
		keyNum = Key();
		if (keyNum)
		{
			Buzzer_Time(100);
			Nixie(1, keyNum);
		}
	}
}