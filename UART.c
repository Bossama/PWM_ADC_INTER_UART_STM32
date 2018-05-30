#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "misc.h"


void USART_Config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;

	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	  /* Enable UART clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	  /* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

	  /* Connect PXx to USARTx_Rx*/
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  USART_InitStructure.USART_BaudRate = 2400;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	  /* USART configuration */
	  USART_Init(USART1, &USART_InitStructure);

	  /* Enable USART */
	  USART_Cmd(USART1, ENABLE);

}
