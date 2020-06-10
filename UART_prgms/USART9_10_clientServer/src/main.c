/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

//USART WORKING CODE WITH RX INTERREPT
#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"
#include<string.h>
#include<stdio.h>

#define COMM_START	'*'
#define COMM_STOP	'&'
#define COMM_NEXT	'?'
#define COMM_PAUSE	'!'


char  cmd = ' ';
char comm_buf[256];
extern int RXflag = 0;

void delay(int counter)
{
	int i;
	for(i = 0; i < counter*1000; i++)
	{

	}

}

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


void USART1_InitMode()
{

		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
		/* Configure USART1 pins: Rx and Tx ----------------------------*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/* Enable USART1 IRQ */
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1,ENABLE);
		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);



}

void USART1_Senddata(char *comm_buf)
{
	for(int i=0; i<strlen(comm_buf); i++)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
					//{

					//}
		USART_SendData(USART1,comm_buf[i]);

	}

	USART_SendData(USART1, '\r');
	USART_SendData(USART1, '\n');

}

//**************************************************************************************
void USART1_IRQHandler(void)
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // Received characters modify string
	{
	cmd = USART_ReceiveData(USART1);
	if (cmd)
	{
		RXflag=1;
	}

	}
}


int main(void)
{
	USART1_InitMode();
	while(1)
	{

		/*if(RXflag)
		{
			RXflag=0;
			sprintf(comm_buf,"START");
			USART1_Senddata(comm_buf);
		}*/

		switch(cmd)
					{
					case COMM_START:
						RXflag=0;
						cmd = ' ';
						memset(&comm_buf, 0 , 256);
						sprintf(comm_buf,"START");
						USART1_Senddata(comm_buf);
						break;
					case COMM_STOP:
						RXflag=0;
						cmd = ' ';
						memset(&comm_buf, 0 , 256);
						sprintf(comm_buf,"STOP");
						USART1_Senddata(comm_buf);
						break;
					case COMM_NEXT:
						RXflag=0;
						cmd = ' ';
						memset(&comm_buf, 0 , 256);
						sprintf(comm_buf,"GIVE ME NEXT");
						USART1_Senddata(comm_buf);
						break;
					case COMM_PAUSE:
						RXflag=0;
						cmd = ' ';
						memset(&comm_buf, 0 , 256);
						sprintf(comm_buf,"PAUSE");
						USART1_Senddata(comm_buf);
						break;

					}



	}

}





