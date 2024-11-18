#include <REGX52.H>
// PWM
sbit LED = P2^0;

void Delay(unsigned char n)
{
	while(n--);
}

void main() 
{
	unsigned char time, i;
	
	while(1)
	{
		for(time = 0; time < 100; time++) {
			for(i = 0; i < 20; i++) {
				LED = 0;
				Delay(time);
				LED = 1;
				Delay(100-time);
			}
		}
		
		for(time = 100; time > 0; time--) {
			for(i = 0; i < 20; i++) {
				LED = 0;
				Delay(time);
				LED = 1;
				Delay(100-time);
			}
		}
	}
	
}