
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

/*--------------Signal MLI sur sortie Timer 1 canal 1  PE9 ------------------*/

TIM_TimeBaseInitTypeDef timerInitStructure;
TIM_OCInitTypeDef outputChannelInit = {0,};

void InitializeTimer (int period)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	GPIO_InitTypeDef GPIO_PWM;
	   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	   GPIO_PWM.GPIO_Pin =  GPIO_Pin_9;
	   GPIO_PWM.GPIO_Mode = GPIO_Mode_AF;
	   GPIO_PWM.GPIO_Speed = GPIO_Speed_50MHz;
	   GPIO_Init(GPIOE, &GPIO_PWM);

		  /* Connect TIM pins to AF2 */
	 GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);

	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	    timerInitStructure.TIM_Prescaler = 16;
	    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	    timerInitStructure.TIM_Period = period;
	    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	    timerInitStructure.TIM_RepetitionCounter = 0;
	    TIM_TimeBaseInit(TIM1, &timerInitStructure);
	    TIM_Cmd(TIM1, ENABLE);
	    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

	void InitializePWMChannel(int duty)  // procedure Rapport cyclique
	{
	    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	    outputChannelInit.TIM_Pulse=duty;
	    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

	    TIM_OC1Init(TIM1, &outputChannelInit);
	    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	}

	void SetTimerPer(int period)   // procedure Frequence
	{
	    timerInitStructure.TIM_Period = period;
	    TIM_TimeBaseInit(TIM1, &timerInitStructure);

	}
	void SetPWM(int duty)          // procedure Rapport cyclique
	{
	    outputChannelInit.TIM_Pulse=duty;
	    TIM_OC1Init(TIM1, &outputChannelInit);
	}
