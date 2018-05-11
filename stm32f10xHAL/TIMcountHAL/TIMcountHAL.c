
#include  "TIMcountHAL.h"


void  TIMcount_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


	/*IO����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_DeInit(TIM3);

	TIM_TimeBaseStructure.TIM_Period = 65535;                    //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0;                     //ʱ��Ԥ��Ƶ��CK_INTʱ���ṩ��������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //ʱ�ӱ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);


	//�����ⲿ����ʱ��
	TIM_TIxExternalClockConfig(TIM3, TIM_TIxExternalCLK1Source_TI2, TIM_ICPolarity_Rising, 0x0);
	TIM_ETRClockMode1Config(TIM3, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted,0x0);


	TIM_SetCounter(TIM3, 0x0000);
	TIM_Cmd(TIM3, ENABLE);
}



