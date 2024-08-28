#include <REGX52.H>

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

void main()
{

	P2 = 0xFF;
	
	while(1)
	{
		if (P3_2 == 0)
		{
			Delay(30);
			while(P3_2 == 0);
			Delay(30);
			P2--;
		}	
	}
	
	
}
