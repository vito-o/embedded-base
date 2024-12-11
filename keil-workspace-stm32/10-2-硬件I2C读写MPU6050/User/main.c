#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

uint8_t key;

int main()
{
	OLED_Init();
	

	MPU6050_init();
	uint8_t ID = MPU6050_GetID();
	int16_t AccX, AccY, AccZ, GyroX, GyroY, GyroZ;
	
	while(1)
	{
			MPU6050_GetData(&AccX, &AccY, &AccZ, &GyroX, &GyroY, &GyroZ);
			OLED_ShowSignedNum(2, 1, AccX, 5);
			OLED_ShowSignedNum(3, 1, AccY, 5);
			OLED_ShowSignedNum(4, 1, AccZ, 5);
		
			OLED_ShowSignedNum(2, 8, GyroX, 5);
			OLED_ShowSignedNum(3, 8, GyroY, 5);
			OLED_ShowSignedNum(4, 8, GyroZ, 5);
	}
}
