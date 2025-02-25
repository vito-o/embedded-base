#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"

#define KEY1   HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) //读取KEY1引脚状态（sw3）
#define KEY2   HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) //读取KEY2引脚状态（sw4） 
// #define KEY3   HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) //读取KEY3引脚状态（sw5）
// #define KEY4   HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin) //读取KEY4引脚状态（sw6）

#define KEY1_PRESS 1 //KEY1按下
#define KEY2_PRESS 2 //KEY2按下    
// #define KEY3_PRES 3 //KEY3按下
// #define KEY4_PRES 4 //KEY4按下

uint8_t Key_Detect(void); //按键检测函数

#endif // _KEY_H_
