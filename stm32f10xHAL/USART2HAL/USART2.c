

#include  "USART2.h"

void USART2_GPIOInit(void)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;


#if USART2_GPIO_DENFIN == USART2_GPIO_A
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART2，GPIOA时钟
		 //USART2_TX   PA.2
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
   GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA2
   
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA3
#endif


#if USART2_GPIO_DENFIN == USART2_GPIO_D
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOD, ENABLE);	//使能，GPIOD时钟
 	  GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE); //CAN1
	  
	 //USART2_TX   PD.5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOD, &GPIO_InitStructure); //
   
    //USART2_RX	  PD.6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOD, &GPIO_InitStructure);  //
#endif

#if  USART2_RS485_TRHAL == 1
//485设置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//使能，GPIOD时钟
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
	USART_DeInit(USART2);  //复位串口2
	
	//GPIO 初始化设置
	USART2_GPIOInit();
	
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口

   //USART2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
   
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
  USART_Cmd(USART2, ENABLE);                    //使能串口 

}

//串口发送数据函数
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

//串口发送字符串
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

void USART2_IRQHandler(void)                	//串口1中断服务程序
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		 USART_ReceiveData(USART2);//(USART2->DR);	//读取接收到的数据
		}
}





