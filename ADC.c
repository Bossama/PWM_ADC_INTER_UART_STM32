#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"

void ADC1_Config(void)
{
  //for ADC1 on PA1 & PA2 using Canal 1
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  /*1.Enable the ADC interface clock using APB2 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); /*Enable GPIOA clock */

  //for ADC1 IN PA1 ET PA2
    GPIO_InitTypeDef  GPIO_In_ADC;
    GPIO_StructInit(&GPIO_In_ADC); /*Fills each GPIO_InitStruct member with its default value.*/
    GPIO_In_ADC.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_In_ADC.GPIO_Mode = GPIO_Mode_AN;
    GPIO_In_ADC.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_In_ADC);

  ADC_InitTypeDef  ADC_1;
  ADC_StructInit(&ADC_1);
  ADC_1.ADC_Resolution = ADC_Resolution_12b;
  ADC_1.ADC_ScanConvMode = DISABLE;
  ADC_1.ADC_ContinuousConvMode = DISABLE;
  ADC_1.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_1.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_1.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_1);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_480Cycles);  /* ADC1 cannal 1 */
  ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);
  ADC_Cmd(ADC1, ENABLE);    //The ADC is powered ON
  ADC_ITConfig ( ADC1, ADC_IT_EOC , ENABLE);

  NVIC_InitTypeDef N;  /* ADC Interruption ENABLE */
  N.NVIC_IRQChannel = ADC_IRQn;
  N.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&N);

}


