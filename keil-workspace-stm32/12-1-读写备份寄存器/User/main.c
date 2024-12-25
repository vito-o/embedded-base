#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint16_t ArrayWrite[] = {0x1234, 0x5678};
uint16_t ArrayRead[2];

uint8_t keyNum;

int main()
{
	OLED_Init();
	Key_init();
	
	OLED_ShowString(1, 1, "W:");
	OLED_ShowString(2, 1, "R:");
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);		// 开启PWR的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);		// 开启BKP的时钟
	
	// 备份寄存器访问使能
	PWR_BackupAccessCmd(ENABLE);													// 使用PWR开启对备份寄存器的访问
	
	while(1)
	{
		keyNum = getKey();
		
		if (keyNum == 1)
		{
			ArrayWrite[0]++;
			ArrayWrite[1]++;
			
			// 写入测试数据到备份寄存器
			BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);
			BKP_WriteBackupRegister(BKP_DR2, ArrayWrite[1]);
			
			OLED_ShowHexNum(1, 3, ArrayWrite[0], 4);
			OLED_ShowHexNum(1, 8, ArrayWrite[1], 4);
		}
		
		// 读取备份寄存器的数据
		ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
		ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);
		
		OLED_ShowHexNum(2, 3, ArrayRead[0], 4);
		OLED_ShowHexNum(2, 8, ArrayRead[1], 4);
	}
}
