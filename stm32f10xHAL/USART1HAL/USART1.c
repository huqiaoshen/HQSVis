
#include  "USART1.h"


void USART1_Init(unsigned int bound)
{
  //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	USART_DeInit(USART1);  //��λ����1
	 //USART1_TX   PA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
  //USART1_RX	  PA.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10


  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������

  //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�

  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}



//���ڷ������ݺ���
void USART1_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	USART_ClearFlag(USART2,USART_FLAG_TC); //��� ��λ ���� ��һ�η��� ����ֶ�ʧ��һ������
	for(i = 0;i < length;i ++)
	{			
		USART1->DR = *(send_buff+i);
		while((USART1->SR&0X40)==0);	
	}	
}



//���ڷ����ַ���
void USART1_Send_String(unsigned char *string)
{
  while(*string!='\0')
	{
	   USART1->DR=*string;
     while(!(USART1->SR&0x40));
	   string++;
	}  
}



void USART1_IRQHandler(void)                	//����1�жϷ������
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
		{
		 USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		}
}



