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
			

#include<stdio.h>
char ReceivedData;


void SystickDelayMS(int n)
{
	SysTick->LOAD = 8000; // Reload with number of clocks per milli seconds
	SysTick->VAL = 0; // Clear current value register
	SysTick->CTRL = 0x5; // enable systick

	for(int i=0; i<n; i++)
	{
		// wait until the count flag is set

		while((SysTick->CTRL&0x10000)==0)
		{

		}
	}

	SysTick->CTRL = 0; // disable systick

}





void USART_setupInit(void)
{
	USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

		/* Configure USART2 pins: Rx and Tx ----------------------------*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;// Push pull
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		USART_Init(USART2, &USART_InitStructure);
			USART_Cmd(USART2,ENABLE);


}




int main(void)
{
	char ch = '?';
	USART_setupInit();

	//while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
	USART_SendData(USART2, ch);
	if(ch=='?')
	{
		ReceivedData = USART_getData(USART2);
	}


}
