#include "led.h"

void Led_on(LED led)
{
  HAL_GPIO_WritePin(GPIOA, led, GPIO_PIN_RESET);
}

void Led_off(LED led)
{
  HAL_GPIO_WritePin(GPIOA, led, GPIO_PIN_SET);
}

void Led_toggle(LED led)
{
  HAL_GPIO_TogglePin(GPIOA, led);
}

// 对一组LED灯，全开全关
void LED_onAll(LED leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        Led_on(leds[i]);
    }
}

void LED_offAll(LED leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        Led_off(leds[i]);
    }
}

