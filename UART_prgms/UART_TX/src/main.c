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

void delayMs(int delay)
{
	int i;
	for(i = 0; i < delay*1000; i++)
	{

	}
}


void USART2_Init(void)
{
		USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
		RCC->APB1ENR |= 0X20000;//APB1 bit 17 :USART2

		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

		//0x48000020
		//GPIOA->MODER = 0X2; //set PA2 AF  0010 0000
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIOA->AFR[0] = 0x0100; // PA2 AF is AF1 SO PA2 is 3rd nibble

		USART_InitStructure.USART_BaudRate = 9600;
		//USART2->BRR = 480000 / 96; /* (1) Oversampling by 16, 9600 baud OR 0x0683 */
		USART2->CR1 = 0x0008; // enable TE bit of CR1 register
		USART2->CR1 |= 0x2000; // MME mute mode enable ,enable rxr in active mode

}

void USART_Write(int ch)
{
	//Wait while TX buffer is empty
	//while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET); // instead of ; u can use {}
	USART2->TDR = (ch & 0xFF);

}



int main(void)
{
	USART2_Init();

	while(1)
	{
		USART_Write('H');
		USART_Write('E');
		USART_Write('\r');
		USART_Write('\n');
		delayMs(500);
	}

}





