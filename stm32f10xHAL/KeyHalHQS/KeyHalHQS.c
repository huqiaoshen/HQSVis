#include "KeyHalHQS.h"

void HQSKeyHalIint(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD| RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					       //根据设定参数初始化GPIOE

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					       //根据设定参数初始化GPIOE
}

uint8 HQSKeyHalGetDate(void)
{
	uint8 date;
	date = 0;
	date |= GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13);
	date |= GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)<<1;
	return date;
}

