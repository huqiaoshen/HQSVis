
#include  "UART4.h"


void UART4_Init(unsigned int bound)
{
//    //GPIO�˿�����
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
//	
//	USART_DeInit(UART4); 

//	 //UART4_TX   PC10
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC10
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//  GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PA9
//   
//    //UART4_RX	  PC11
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//  GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PA10


//   //USART ��ʼ������

//	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

//  USART_Init(UART4, &USART_InitStructure); //��ʼ������

//  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);



 NVIC_InitTypeDef NVIC_InitStructure;
 GPIO_InitTypeDef GPIO_InitStructure;
 USART_InitTypeDef USART_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); 
 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC, &GPIO_InitStructure);
 
 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 GPIO_Init(GPIOC, &GPIO_InitStructure);

 
 USART_InitStructure.USART_BaudRate = bound;
 USART_InitStructure.USART_WordLength = USART_WordLength_8b;
 USART_InitStructure.USART_StopBits = USART_StopBits_1;
 USART_InitStructure.USART_Parity = USART_Parity_No;
 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
 
 USART_Init(UART4, &USART_InitStructure);
 
 USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
 
 USART_Cmd(UART4, ENABLE);
 

 NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
}



//���ڷ������ݺ���
void UART4_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	
	USART_ClearFlag(UART4,USART_FLAG_TC);
	
	for(i = 0;i < length;i ++)
	{			
		UART4->DR = *(send_buff+i);
		while((UART4->SR&0X40)==0);	
	}	
}



//���ڷ����ַ���
void UART4_Send_String(unsigned char *string)
{
  while(*string!='\0')
	{
	   UART4->DR=*string;
     while((UART4->SR&0X40)==0);
	   string++;
	}  
}



void UART4_IRQHandler(void)                	//����1�жϷ������
{
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		 USART_ReceiveData(UART4);//(UART4->DR);	//��ȡ���յ�������
		}
}










