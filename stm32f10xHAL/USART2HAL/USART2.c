

#include  "USART2.h"

void USART2_GPIOInit(void)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;


#if USART2_GPIO_DENFIN == USART2_GPIO_A
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART2��GPIOAʱ��
		 //USART2_TX   PA.2
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
   GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA2
   
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA3
#endif


#if USART2_GPIO_DENFIN == USART2_GPIO_D
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOD, ENABLE);	//ʹ�ܣ�GPIODʱ��
 	  GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE); //CAN1
	  
	 //USART2_TX   PD.5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOD, &GPIO_InitStructure); //
   
    //USART2_RX	  PD.6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOD, &GPIO_InitStructure);  //
#endif

#if  USART2_RS485_TRHAL == 1
//485����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//ʹ�ܣ�GPIODʱ��
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7; //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;;
    GPIO_Init(GPIOD, &GPIO_InitStructure); //
    RS_485_RX_USART2EN();
#endif

}


void USART2_Init(unsigned int bound)
{

	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_DeInit(USART2);  //��λ����2
	
	//GPIO ��ʼ������
	USART2_GPIOInit();
	
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure); //��ʼ������

   //USART2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

}

//���ڷ������ݺ���
void USART2_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
#if  USART2_RS485_TRHAL == 1
	RS_485_TX_USART2EN();
#endif
	for(i = 0;i < length;i ++)
	{			
		USART2->DR = *(send_buff+i);
		while((USART2->SR&0X40)==0);	
	}	
#if  USART2_RS485_TRHAL == 1
	RS_485_RX_USART2EN();
#endif
}

//���ڷ����ַ���
void USART2_Send_String(unsigned char *string)
{
	USART_ClearFlag(USART2,USART_FLAG_TC);
#if  USART2_RS485_TRHAL == 1
	RS_485_TX_USART2EN();
#endif
  while(*string!='\0')
	{
	   USART2->DR=*string;
     while(!(USART2->SR&0x40));
	   string++;
	}  
#if  USART2_RS485_TRHAL == 1
	RS_485_RX_USART2EN();
#endif
}

void USART2_IRQHandler(void)                	//����1�жϷ������
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		 USART_ReceiveData(USART2);//(USART2->DR);	//��ȡ���յ�������
		}
}




