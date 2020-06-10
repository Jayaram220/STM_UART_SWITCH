/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"

extern int portApin15counter=0;
int ledStatus = 0x0200;
void EXTI4_15_IRQHandler(void)
{

    if( (EXTI->IMR & EXTI_IMR_MR15) && (EXTI->PR & EXTI_PR_PR15) )
      {
    	portApin15counter=1;
    	while(GPIOA->IDR & GPIO_IDR_15){} // Wait for the button
    	EXTI->PR |= EXTI_PR_PR15;
      }


}



int main(void)
{
	 RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	 GPIOA->MODER &= ~(GPIO_MODER_MODER15);
	 GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR15);
	 GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR15);
	 RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	 GPIOC->MODER |= (GPIO_MODER_MODER9_0);
	 GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_9);
	 GPIOC->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR9);

	 GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR9_0);



	SYSCFG->EXTICR[4]  = SYSCFG_EXTICR4_EXTI15_PA;
	EXTI->RTSR = EXTI_RTSR_TR15;
	EXTI->IMR = EXTI_IMR_MR15;
	NVIC_SetPriority(EXTI4_15_IRQn, 1);
	NVIC_EnableIRQ(EXTI4_15_IRQn);


	while(1)
	{
		if(portApin15counter)
			{
				portApin15counter = 0;
			    GPIOC -> ODR ^= ledStatus; // Toggle the LED if you get here
			}
		else
		{
			GPIOC -> ODR = 0x00;
		}
	}


}
