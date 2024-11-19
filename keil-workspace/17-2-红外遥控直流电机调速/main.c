#include <REGX52.H>
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"

unsigned char command, speed;

void main() 
{
	Motor_Init();
	IR_init();
	
	while(1)
	{
			if (IR_getDataFlag())
			{
				command = IR_getCommand();
				
				if(command==IR_0){speed=0;}		//根据遥控器命令码设置速度
				if(command==IR_1){speed=1;}
				if(command==IR_2){speed=2;}
				if(command==IR_3){speed=3;}
				
				if(speed==0) Motor_SetSpeed(0);
				if(speed==1) Motor_SetSpeed(20);
				if(speed==2) Motor_SetSpeed(55);
				if(speed==3) Motor_SetSpeed(100);
			}
			
			Nixie(1, speed);
	}
	
}

