#include "key.h"
// led  A0

// 按键 B12
// 这里是通过按键，触发外部中断
void Key_init()
{
  	// 1.时钟配置
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	// 2.GPIO工作模式配置
  // B12 为下拉输入: MODE=00 CNF=10  ODR=0
  GPIOB->CRH &= ~GPIO_CRH_MODE12; 
	GPIOB->CRH |= GPIO_CRH_CNF12_1; 
  GPIOB->CRH &= ~GPIO_CRH_CNF12_0;
  GPIOB->ODR &= ~GPIO_ODR_ODR12; //设置为0， 即下拉电阻

  //3.配置AFIO 配置PF12引脚为外部中断 AFIO_EXTICR4  0001
  AFIO->EXTICR[3] &= ~AFIO_EXTICR4_EXTI12;
  AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PB;

  //4.配置EXIT
  //4.1配置上升沿触发 RTSR TR12 = 1
  EXTI->RTSR |= EXTI_RTSR_TR12;
  //4.2开启LINE12，配置中断屏蔽寄存器 = 1
  EXTI->IMR |= EXTI_IMR_MR12;

  // 5.配置NVIC
  // 5.1配置优先级组(3-7) 配置3表示4个二进制位全部用于表示抢占优先级
  NVIC_SetPriorityGrouping(3);
  // 5.2配置优先级，参数1为中断号
  NVIC_SetPriority(EXTI15_10_IRQn, 3);
  // 5.3使能LINE
  NVIC_EnableIRQ(EXTI15_10_IRQn);

}


void EXTI15_10_IRQHandler(void)
{
  // 务必一定必须要清除中断标志位
  EXTI->PR |= EXTI_PR_PR12;

  Delay_ms(5);

  if ((GPIOB->IDR & GPIO_IDR_IDR12) != 0)
  {
    Led_toggle(Led1);
  }
	
	
}
