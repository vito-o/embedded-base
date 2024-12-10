#include "led.h"

void Led_init()
{
  	// 1.时钟配置
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	

	// 2.GPIO工作模式配置
	GPIOA->CRL &= ~GPIO_CRL_CNF0; 
	GPIOA->CRL |= GPIO_CRL_MODE0;

	GPIOA->CRL &= ~GPIO_CRL_CNF1; 
	GPIOA->CRL |= GPIO_CRL_MODE1;

	GPIOA->CRL &= ~GPIO_CRL_CNF2; 
	GPIOA->CRL |= GPIO_CRL_MODE2;

	// 3.在PA0,PA1,PA2输出高电平，默认关灯
	Led_off(Led1);
	Led_off(Led2);
	Led_off(Led3);
}

void Led_on(uint16_t led)
{
  GPIOA->ODR &= ~led;
}

void Led_off(uint16_t led)
{
  GPIOA->ODR |= led;
}

void Led_toggle(uint16_t led)
{
  if ((GPIOA->IDR & led) == 0)
  {
    Led_off(led);
  }
  else {
    Led_on(led);
  }
}

// 对一组LED灯，全开全关
void LED_onAll(uint16_t leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        Led_on(leds[i]);
    }
}

void LED_offAll(uint16_t leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        Led_off(leds[i]);
    }
}

