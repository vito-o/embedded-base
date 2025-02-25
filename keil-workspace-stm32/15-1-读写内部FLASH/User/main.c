#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"
#include "Key.h"

uint8_t key;

int main()
{
	OLED_Init();
	Store_Init();
	Key_init();

	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Flag:");
	OLED_ShowString(2, 1, "Data:");
	
	while(1)
	{
		key = getKey();
		
		if (key == 1)
		{
			Store_Data[1] ++;		//变换测试数据
			Store_Data[2] += 2;
			Store_Data[3] += 3;
			Store_Data[4] += 4;
			Store_Save();			//将Store_Data的数据备份保存到闪存，实现掉电不丢失
		}
		
		if (key == 2)
		{
			Store_Clear();			// 将store_data中的数据清除
		}
		
		OLED_ShowHexNum(1, 6, Store_Data[0], 4); // 显示自定义标记位
		
		OLED_ShowHexNum(3, 1, Store_Data[1], 4);
		OLED_ShowHexNum(3, 6, Store_Data[2], 4);
		OLED_ShowHexNum(4, 1, Store_Data[3], 4);
		OLED_ShowHexNum(4, 6, Store_Data[4], 4);
	}
}
