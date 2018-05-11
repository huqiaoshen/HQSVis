
#include "PVDHAL.h"


void PVDInint()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/*比较电压设置*/
	PWR_PVDLevelConfig(PWR_PVDLevel_2V3);
	PWR_PVDCmd(ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = PVD_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);//中断配置

	EXTI_DeInit();
	EXTI_ClearITPendingBit(EXTI_Line16);
	EXTI_InitStructure.EXTI_Line = EXTI_Line16;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//EXTI_Trigger_Falling   ;//EXTI_Trigger_Rising; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

}


 //PVD中断函数如下
 void PVD_IRQHandler(void)
 {

	 EXTI_ClearITPendingBit(EXTI_Line16); //必须在if外面。

	 if (PWR_GetFlagStatus(PWR_FLAG_PVDO)) //低于由PLS[2:0]选定的PVD阀值
	 {
		 PWR_ClearFlag(PWR_FLAG_PVDO);
		
		 //在这里进行 掉电前要处理的任务



	 }
	 else   //高于由PLS[2:0]选定的PVD阀值
	 {
		 PWR_ClearFlag(PWR_FLAG_PVDO);
		 
	 }

 }




