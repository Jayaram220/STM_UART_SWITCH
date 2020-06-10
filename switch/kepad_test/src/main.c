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

#include "stm32f0xx_conf.h"
uint32_t TickValue=0;
#define PLL_MUL_X 2
void TimingDelay_Decrement(void)
{
TickValue--;
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


void initgpio()
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC, ENABLE);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_8 ;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init(GPIOC, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init(GPIOB, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_Init(GPIOA, &GPIO_InitStructure);

// input pins

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void display(int b)
{
switch(b)
{
	case 0: GPIOA->ODR = 0x0007; //0
	GPIOC->ODR = 0x0007;
	SystickDelayMS(1000);
	break;
	case 1:
	GPIOA->ODR = 0x0001; //1
	GPIOC->ODR = 0x0004;
	SystickDelayMS(1000);
	break;
	case 2:
	GPIOA->ODR = 0x000B; //2
	GPIOC->ODR = 0x0003;
	SystickDelayMS(1000);
	break;
	case 3:
	GPIOA->ODR = 0x000B; //3
	GPIOC->ODR = 0x100;
	SystickDelayMS(2000);
	GPIOC->ODR = 0x000;
	GPIOC->ODR = 0x100;
	SystickDelayMS(2000);
	GPIOC->ODR = 0x000;
	GPIOC->ODR = 0x100;
	SystickDelayMS(2000);
	GPIOC->ODR = 0x000;
	break;
	case 4:
	GPIOA->ODR = 0x000D; //4
	GPIOC->ODR = 0x0004;
	SystickDelayMS(1000);
	break;
	case 5:
	GPIOA->ODR = 0x000E; //5
	GPIOC->ODR = 0x0006;
	SystickDelayMS(1000);
	break;
	case 6:
	GPIOA->ODR = 0x000E; //6
	GPIOC->ODR = 0x0007;
	SystickDelayMS(1000);
	break;
	case 7:
	GPIOA->ODR = 0x0003; //7
	GPIOC->ODR = 0x0004;
	SystickDelayMS(1000);
	break;
	case 8:
	GPIOA->ODR = 0x000F; //8
	GPIOC->ODR = 0x0007;
	delay_ms(1000);
	break;
	case 9:
	GPIOA->ODR = 0x000F; //9
	GPIOC->ODR = 0x0006;
	delay_ms(1000);
	break;
	case 10:
	GPIOA->ODR = 0x000F; //*
	GPIOC->ODR = 0x0000;
	delay_ms(1000);
	break;
	case 11:
	GPIOA->ODR = 0x0008; //#
	GPIOC->ODR = 0x000F;
	delay_ms(1000);
	break;
}
return ;
}

int main(void)
{

initgpio();

while(1)
{
GPIOC->BSRR = GPIO_Pin_5;//set bit as high
GPIOB->BRR = GPIO_Pin_0;//set bit as low
GPIOB->BRR = GPIO_Pin_1;//set bit as low
{
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))//read input bit PB12
display(3);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)) //read input bit PB11
display(6);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)) //read input bit PB10
display(9);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)) //read input bit PB2
display(11);
}
GPIOC->BRR = GPIO_Pin_5;//set bit as low
GPIOB->BSRR = GPIO_Pin_0;//set bit as high
GPIOB->BRR = GPIO_Pin_1;//set bit as low
{
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
display(2);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
display(5);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
display(8);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
display(0);

}
GPIOC->BRR = GPIO_Pin_5;//set bit as low
GPIOB->BRR = GPIO_Pin_0;//set bit as low
GPIOB->BSRR = GPIO_Pin_1;//set bit ashigh
{
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
display(1);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
display(4);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
display(7);
if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
display(10);

}


}


}


