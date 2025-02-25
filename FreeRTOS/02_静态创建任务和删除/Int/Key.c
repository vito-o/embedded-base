#include "Key.h"

/**
 * @description: 检测按键
 * @return {*} 返回按键值
 */
uint8_t Key_Detect(void)
{
  uint8_t res;
  if(KEY1 == GPIO_PIN_RESET || KEY2 == GPIO_PIN_RESET)
  {
    HAL_Delay(10); // 消抖
    if (KEY1 == GPIO_PIN_RESET) res = KEY1_PRESS;
    if (KEY2 == GPIO_PIN_RESET) res = KEY2_PRESS;
    
  }
  return res;
}
