#include <intrins.h>

//延时1s
void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		
		xms--;
	}
}


void Delay_10us(unsigned char n)
{
	while(n--) {
		unsigned char data i;

		i = 2;
		while (--i);
	}	
}

void Delay_50us(unsigned char n)
{
	while(n--) {
		unsigned char data i;

		_nop_();
		i = 20;
		while (--i);
	}
}

void Delay_60us(unsigned char n)
{
	while(n--) {
		unsigned char data i;

		i = 25;
		while (--i);
	}
}