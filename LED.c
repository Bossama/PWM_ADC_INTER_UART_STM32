#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


void LED_Config (void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); /*Enable GPIO "D" clock */
  GPIO_InitTypeDef GPIO_Led;
  GPIO_StructInit(&GPIO_Led);
  //Activation LED_15,14,13,12
  GPIO_Led.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_5;
  GPIO_Led.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Led.GPIO_OType = GPIO_OType_PP;
  GPIO_Led.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Led.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_Led);
}
