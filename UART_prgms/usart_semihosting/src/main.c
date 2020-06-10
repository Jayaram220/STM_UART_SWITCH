/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"
			

char msg[250];
char usr_msg[250];
char ReceivedData;
char ReceivedDataArray[100];
static void prvSetupUART(void)
{
	USART_InitTypeDef USART_InitStructure;
				GPIO_InitTypeDef GPIO_InitStructure;
				RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

				memset(&GPIO_InitStructure,0,sizeof(GPIO_InitStructure));

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
				USART_InitStructure.USART_BaudRate = 115200;
				USART_InitStructure.USART_WordLength = USART_WordLength_8b;
				USART_InitStructure.USART_StopBits = USART_StopBits_1;
				USART_InitStructure.USART_Parity = USART_Parity_No;
				USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
				USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
				//AF mode settings for pin
				USART_Init(USART2, &USART_InitStructure);
				USART_Cmd(USART2,ENABLE);


}


static void prvSetupHardware(void)
{
	prvSetupUART();

}

void printMsg(char *msg)
{
	for(uint32_t i=0; i< strlen(msg); i++)
	{
		//while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
		USART_SendData(USART2,msg[i]);

	}

}

void USART2_Read(void)
{
	for(uint32_t j=0; j< strlen(msg); j++)
		{
		ReceivedData = USART_ReceiveData(USART2);
		ReceivedDataArray[j] = ReceivedData;
		}
	printf("%s",ReceivedDataArray);
}

int main(void)
{
	prvSetupHardware();

	sprintf(usr_msg,"ABC");
	printMsg(usr_msg);
	USART2_Read();


}
