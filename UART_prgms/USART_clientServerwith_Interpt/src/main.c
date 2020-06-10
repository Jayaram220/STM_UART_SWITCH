/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

// APB1 connected to 17th bit :USART2
//USART connected to PA2


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





void USART2_InitMode()
{
				USART_InitTypeDef USART_InitStructure;
				GPIO_InitTypeDef GPIO_InitStructure;
				RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
				GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);//PA2 TX
				GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);//PA3 RX

				/* Configure USART2 pins: Rx and Tx ----------------------------*/
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;// Push pull
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				//USART peripheral
				USART_InitStructure.USART_BaudRate = 9600;
				USART_InitStructure.USART_WordLength = USART_WordLength_8b;
				USART_InitStructure.USART_StopBits = USART_StopBits_1;
				USART_InitStructure.USART_Parity = USART_Parity_No;
				USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
				USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
				//AF mode settings for pin
				USART_Init(USART2, &USART_InitStructure);
				USART_Cmd(USART2,ENABLE);




}



void USART2_Senddata(char *comm_buf)
{
	for(int i=0; i<strlen(comm_buf); i++)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
					//{

					//}
		USART_SendData(USART2, comm_buf[i]);

	}
	SystickDelayMS(1000);
	//delay(100);
	USART_SendData(USART2, '\r');
	USART_SendData(USART2, '\n');

}


int main(void)
{

			USART2_InitMode();
			while(1)
			{

			while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
			cmd = USART_ReceiveData(USART2);


			switch(cmd)
			{
			case COMM_START:
				memset(&comm_buf, 0 , 256);
				sprintf(comm_buf,"START");
				USART2_Senddata(comm_buf);
				break;
			case COMM_STOP:
				memset(&comm_buf, 0 , 256);
				sprintf(comm_buf,"STOP");
				USART2_Senddata(comm_buf);
				break;
			case COMM_NEXT:
				memset(&comm_buf, 0 , 256);
				sprintf(comm_buf,"GIVE ME NEXT");
				USART2_Senddata(comm_buf);
				break;
			case COMM_PAUSE:
				memset(&comm_buf, 0 , 256);
				sprintf(comm_buf,"PAUSE");
				USART2_Senddata(comm_buf);
				break;

			}
			SystickDelayMS(1000);
			//delay(3000);
			}

}
