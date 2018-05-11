
#include "PVDHAL.h"


void PVDInint()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/*�Ƚϵ�ѹ����*/
	PWR_PVDLevelConfig(PWR_PVDLevel_2V3);
	PWR_PVDCmd(ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = PVD_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);//�ж�����

	EXTI_DeInit();
	EXTI_ClearITPendingBit(EXTI_Line16);
	EXTI_InitStructure.EXTI_Line = EXTI_Line16;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//EXTI_Trigger_Falling   ;//EXTI_Trigger_Rising; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

}


 //PVD�жϺ�������
 void PVD_IRQHandler(void)
 {

	 EXTI_ClearITPendingBit(EXTI_Line16); //������if���档

	 if (PWR_GetFlagStatus(PWR_FLAG_PVDO)) //������PLS[2:0]ѡ����PVD��ֵ
	 {
		 PWR_ClearFlag(PWR_FLAG_PVDO);
		
		 //��������� ����ǰҪ����������



	 }
	 else   //������PLS[2:0]ѡ����PVD��ֵ
	 {
		 PWR_ClearFlag(PWR_FLAG_PVDO);
		 
	 }

 }



