#include <REGX52.H>
#include "Delay.h"

/*
	获取独立按键键码
*/
unsigned char Key(void)
{
	unsigned char keyNumber = 0;
	
	if(P3_1==0) {Delay(20);while(P3_1==0);Delay(20);keyNumber=1;}
	if(P3_0==0) {Delay(20);while(P3_0==0);Delay(20);keyNumber=2;}
	if(P3_2==0) {Delay(20);while(P3_2==0);Delay(20);keyNumber=3;}
	if(P3_3==0) {Delay(20);while(P3_3==0);Delay(20);keyNumber=4;}
	
	return keyNumber;
}