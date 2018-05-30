#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"


    // int R1,R2;
    uint8_t K1=0;
    uint16_t ADC_CH2, ADC_CH1, Tp=1000; //  val Tp [100 ... 1000] 100->100us  1000 -> 1ms
    uint32_t Rc=100;
    uint8_t ch=1,i;

    //uint8_t V=0; // valeur de tension

    void Timer3_Interruption_Config (void);
    void ADC1_Config(void);
    void LED_Config(void);
    void InitializeTimer (int period);
    void InitializePWMChannel(int);
    void SetTimerPer(int);
    void SetPWM(int);

    void USART_Config(void);
    void printf();

/*----------------------------- Interruptions with TIMER3 +ADCs ----------------------------------------*/
void TIM3_IRQHandler (void)
{
	GPIO_ToggleBits(GPIOD ,GPIO_Pin_13);
	if (TIM_GetFlagStatus(TIM3 , TIM_FLAG_Update ))
	{
		ADC_SoftwareStartConv(ADC1);
		GPIO_ToggleBits(GPIOD ,GPIO_Pin_5);
		TIM_ClearFlag (TIM3 , TIM_FLAG_Update);
		//K1=0; K2=0;
	}
}

void ADC_IRQHandler (void)
{
	GPIO_ToggleBits(GPIOD ,GPIO_Pin_12);
	if( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
		{
		if(ch==1)
			{
			  ADC_CH1= ADC_GetConversionValue(ADC1);  ch=2;  // get val from chanal 1 ADC1
			  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_15Cycles);  // switch to chanal 2 ADC1
			  ADC_SoftwareStartConv  ( ADC1);
			}
		else if(ch==2)
			{
			  ADC_CH2= ADC_GetConversionValue(ADC1); ch=1;   // get val from chanal 1 ADC1
			  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_15Cycles);  // switch to chanal 1 ADC1

			  Tp = 100 + (ADC_CH1 * 900 >> 12);      // valeur periode T

			  Rc = (uint32_t)(ADC_CH2 * Tp >> 12) ;  // valeur Rapport cyclique Rc

			  SetTimerPer(Tp);     // affecter la valeur Tp au timerInitStructure.TIM_Period
			  SetPWM(Rc);          // affecter la valeur Rc au outputChannelInit.TIM_Pulse
			  K1=1;

			}
			ADC_ClearFlag( ADC1, ADC_FLAG_EOC);
		}
}

/*------------------------------------- Principal ---------------------------------------------*/

int main(void)
{
	Timer3_Interruption_Config();
	ADC1_Config();
	LED_Config();

	InitializeTimer(Tp);
	InitializePWMChannel(Rc);

	USART_Config();
	printf(" ******************************* HELLO ************************************\r\n");


	while(1)
	{
		if (K1){printf(" PERIODE = %d us                        Rapport Cyclique  = %d\r \v ",Tp,Rc);K1=0;}
		//if (K1){printf(" PERIODE = %d us                        Rapport Cyclique  = %d\r \v ",Tp,Rc);K1=0;}
	}
}







