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
	int num = 0;
	P2 = 0xFE;
	while(1)
	{
		if (P3_3 == 0)
		{
			Delay(30);
			while(P3_3 == 0);
			Delay(30);
			num++;
			if (num>=8)
			{
				num = 0;
			}
			P2 = ~(0x01 << num);
		}
		
		if (P3_2 == 0)
		{
			Delay(30);
			while(P3_2 == 0);
			Delay(30);
			num--;
			if (num<0)
			{
				num = 7;
			}
			P2 = ~(0x01 << num);
		}
	}
}