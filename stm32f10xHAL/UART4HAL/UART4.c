
#include  "UART4.h"


void UART4_Init(unsigned int bound)
{
//    //GPIO端口设置
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
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//  GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PA9
//   
//    //UART4_RX	  PC11
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//  GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PA10


//   //USART 初始化设置

//	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

//  USART_Init(UART4, &USART_InitStructure); //初始化串口

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



//串口发送数据函数
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



//串口发送字符串
void UART4_Send_String(unsigned char *string)
{
  while(*string!='\0')
	{
	   UART4->DR=*string;
     while((UART4->SR&0X40)==0);
	   string++;
	}  
}



void UART4_IRQHandler(void)                	//串口1中断服务程序
{
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		 USART_ReceiveData(UART4);//(UART4->DR);	//读取接收到的数据
		}
}











