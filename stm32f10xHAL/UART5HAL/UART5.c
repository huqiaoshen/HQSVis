
#include  "UART5.h"


#define RS_485_RX_EN 	GPIO_ResetBits(GPIOD , GPIO_Pin_0)	//接收使能
#define RS_485_TX_EN 	GPIO_SetBits(GPIOD , GPIO_Pin_0)  	//发送使能

void UART5_GPIO_Init(void);
void UART5_NVIC_Iint(void);

void UART5_Init(unsigned int bound)
{


 USART_InitTypeDef USART_InitStructure;
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); 
 
 /*UART5 Pin Config*/
 UART5_GPIO_Init();
	
 /* Configure 485 */
 USART_InitStructure.USART_BaudRate = bound;
 USART_InitStructure.USART_WordLength = USART_WordLength_8b;
 USART_InitStructure.USART_StopBits = USART_StopBits_1;
 USART_InitStructure.USART_Parity = USART_Parity_No;
 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
 USART_Init(UART5, &USART_InitStructure);
 
 /* Configure NVIC */
 UART5_NVIC_Iint();
	
 USART_Cmd(UART5, ENABLE);
 
}



void UART5_GPIO_Init(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); 
 
	/* Configure UART5 pin: TX */
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC, &GPIO_InitStructure);
 
 /* Configure UART5 pin: RX */
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
 GPIO_Init(GPIOD, &GPIO_InitStructure);

 /* Configure 485EN pin: EN */
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;
 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
 GPIO_Init(GPIOD, &GPIO_InitStructure);
 RS_485_RX_EN;

}

void UART5_NVIC_Iint(void)
{
 NVIC_InitTypeDef NVIC_InitStructure;
 NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 NVIC_Init(&NVIC_InitStructure);
	
 USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
}

void UART5_Config_Iint(void)
{
	
}

//串口发送数据函数
void UART5_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	RS_485_TX_EN;
	for(i = 0;i < length;i ++)
	{			
		UART5->DR = *(send_buff+i);
		while((UART5->SR&0X40)==0);	
	}	
	RS_485_RX_EN;
}



//串口发送字符串
void UART5_Send_String(unsigned char *string)
{
	RS_485_TX_EN;
  while(*string!='\0')
	{
	   UART5->DR=*string;
     while((UART5->SR&0X40)==0);
	   string++;
	}  
	RS_485_RX_EN;
}



void UART5_IRQHandler(void)                	//串口1中断服务程序
{
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		 USART_ReceiveData(UART5);	//读取接收到的数据
		}
}











