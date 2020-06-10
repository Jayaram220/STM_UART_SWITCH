/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include<stdio.h>
#include<string.h>
#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"
			

void USART2_Init(void)
{
	RCC->APB1ENR |= 0X20000;//APB1 bit 17 :USART2
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
		//0x48000020
		GPIOA->AFR[0] = 0x1100; // PA2 and PA3 AF is AF1 SO PA2 is 3rd nibble
		GPIOA->MODER = 0x00A0; //set PA2 AND PA3 AF  1010 0000
		USART2->BRR = 480000 / 96; /* (1) Oversampling by 16, 9600 baud OR 0x0683 */
		USART2->CR1 = 0x000C; // enable TX RX  bit of CR1 register
		USART2->CR1 |= 0x2000; // MME mute mode enable ,enable rxr in active mode

}

int USART_Write(int ch)
{
	//Wait while TX buffer is empty
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET); // instead of ; u can use {}
	USART2->TDR = (ch & 0xFF);
	return ch;
}

int USART_Read(void)
{
	//Wait while TX buffer is empty
	while(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) != SET); // instead of ; u can use {}
	return USART2->RDR;
}

struct __FILE{int handle;};
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c;
	c = USART_Read();
	if(c == '\r')
	{
		USART_Write(c);
		c = '\n';
	}
	USART_Write(c);
	return c;
}

int fputc(int c,FILE *f)
{
	return USART_Write(c);
}



int main(void)
{
	int n;
	char str[100];
	USART2_Init();
	printf("Hello from other side\n");
	fprintf(stdout,"test from stdout\r\n");
	fprintf(stderr,"test from stderr\r\n");

	while(1)
	{
		printf("How old are you ?");
		scanf("%d",&n);
		printf("your age is : %d\r\n",n);
		printf("Enter your first name : ");
		gets(str);
		printf("I Like your style : ");
		puts(str);
		printf("\r\n");

	}

}
