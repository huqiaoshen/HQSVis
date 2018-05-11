
#include	"IOOutHALHQS.h"

void HQSHALIoOutIint(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	//GPIO PA3    RUN_R led   0亮   1灭 
	//GPIO PA4    RUN_G led   0亮   1灭
	//GPIO PA5    off   led   0亮   1灭
	//GPIO PA6    off   led   0亮   1灭
	//GPIO PA7    off   led   0亮   1灭
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					       //根据设定参数初始化GPIOE
	GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);


	//GPIO PC4    off   led   0亮   1灭
	//GPIO PC5    off   led   0亮   1灭
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					       //根据设定参数初始化GPIOE
	GPIO_ResetBits(GPIOC, GPIO_Pin_4 | GPIO_Pin_5);


	//GPIO PB0    off   led   0亮   1灭
	//GPIO PB1    off   led   0亮   1灭
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
}

void HQSHALIoOutContrl(IoOutHQSCreateUse_m ioUse, uint8 level)
{
	switch (ioUse)
	{
	case RUN_LED_G:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		}
		break;
	case RUN_LED_R:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		}
		break;
	case LED_2:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}
		else
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
		}
		break;
	case LED_1:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			
		}
		else
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
		}
		break;
	case LED_4:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		}
		else
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_7);
		
		}
		break;

	case LED_3:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_4);
			
		}
		else
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_4);
		}
		break;

	case LED_6:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		}
		else
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_5);
		}
		break;
	case LED_5:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		}
		else
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		}
		break;

	case LED_8:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		}
		else
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
		}
		break;

	case LED_7:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_2);
		}
		else
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_2);
		}
		break;


		

	case Relay_1:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_15);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_15);
		}
		break;


	case Relay_2:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_14);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_14);
		}
		break;


	case Relay_3:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_13);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_13);
		}
		break;


	case Relay_4:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_12);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_12);
		}
		break;

	case Relay_5:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_11);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_11);
		}
		break;

	case Relay_6:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_10);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_10);
		}
		break;


	case Relay_7:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_9);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_9);
		}
		break;


	case Relay_8:
		if (level == HQSI0OUTlevel_L)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_8);
		}
		else
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_8);
		}
		break;

	case Relay_All:
		if (level == HQSI0OUTlevel_L)
		{
			GPIOE->BRR |= 0XFF00;
		}
		else
		{
			GPIOE->BSRR |= 0XFF00;
		}
		break;


	default:
		break;
	}
}

