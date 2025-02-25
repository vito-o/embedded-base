#include "LED.h"

/**
 * 点亮灯
 */
void LED_Turn_on(LED led)
{
  HAL_GPIO_WritePin(GPIOA, led, GPIO_PIN_SET);
}

/**
 * 熄灭灯
 */
void LED_Turn_off(LED led)
{
  HAL_GPIO_WritePin(GPIOA, led, GPIO_PIN_RESET);
}

/**
 * 翻转灯的状态
 */
void LED_Toggle(LED led)
{
  HAL_GPIO_TogglePin(GPIOA, led);
}

/**
 * 关闭所有led灯
 */
void LED_Turn_off_all(LED led[], uint8_t len)
{
  for (uint8_t i = 0; i < len; i++)
  {
    LED_Turn_off(led[i]);
  }
}
