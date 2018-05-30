#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

/* -------------------------------Creation d'une Interruption chaque 100ms -------------------------------------*/
NVIC_InitTypeDef N;
void Timer3_Interruption_Config (void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef T3;
	T3.TIM_Prescaler = 1600;
	T3.TIM_ClockDivision= TIM_CKD_DIV1;
	T3.TIM_Period=1000;
	T3.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit  ( TIM3,&T3); // fct d'initialisation
	TIM_Cmd( TIM3,ENABLE );        // commander le TIMER
	TIM_ITConfig (TIM3,TIM_IT_Update,ENABLE); // configuration l'interruption de TIMER
    /* ACTIVER LE Vecteur d'interruption de TIMER */
	NVIC_InitTypeDef N;
	N.NVIC_IRQChannel = TIM3_IRQn;
    N.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&N);
}
