
#include  "ETHCFHAL.h"
#include "httpd.h"

static uint32_t EthInitStatus =0;
#define PHYINT_LINK_STATUS     0x2000    //�����ж�
#define PHYINT_SEEP_STATUS     0x1000    //�����ж�
#define PHYINT_SEEPLINK_STATUS 0x3000
/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void ETHCFHAL_GPIO_Config(void)
;˵    ����PHY ETH GPIO ����
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.12.15
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void ETHCFHAL_GPIO_Config(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
		RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);	    //�⺯����ʹ��GPIOʱ��
//��ʼ���õ���GPIO��ʹ��RMII�ӿ�
//MDC          PC1
//MDIO         PA2
//TXEN         PB11
//TXD0         PB12
//TXD1         PB13
//RXER         PB10
//RXD0         PD9
//RXD1         PD10
//RX_DV        PD8
//CLK          PA8
//REF_CLK      PA1
//����PA2  �����������

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//����PC1  �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//����PB11 PB12 PB13 �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	//�ı�RX_DV RXD0��RXD1��ӳ�� 
	GPIO_PinRemapConfig(GPIO_Remap_ETH, ENABLE);

	//����PA0 PA1 ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//����PB10 ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	//����PD8 PD9 PD10 ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//����PA8 �����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void Ethernet_Configuration(void)
;˵    ���� ETH  ����
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.12.15
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void Ethernet_Configuration(void)
{
//ѡ��ӿ���MII����RMII������ʹ��RMII
#ifdef MII_MODE //ѡ��ʹ��MII�ӿ� MII�ӿ���Ҫʱ��25M
	GPIO_ETH_MediaInterfaceConfig(GPIO_ETH_MediaInterface_MII);//�ú���������̫���ӿ�ΪMII

	RCC_MCOConfig(RCC_MCO_HSE);//����MCOʱ����� RCC_MCO_HSE���������ⲿ����ʱ����ΪMCO��������İ��õ�25M�������ṩMII��25Mʱ��

#elif defined RMII_MODE //ѡ��ʹ��RMII�ӿ� RMII�ӿ���Ҫʱ��50M
	GPIO_ETH_MediaInterfaceConfig(GPIO_ETH_MediaInterface_RMII);//�ú���������̫���ӿ�ΪRMII

																//����˼·����PLL3ʱ��ΪMCO�ṩRMII��Ҫ��50Mʱ��
																//ϵͳ��ʼ��STM32��ʱ��Ϊ72M��ʱ��PLL3������Ϊ���ⲿ25M����5��Ƶ 25/5=5M
	RCC_PLL3Config(RCC_PLL3Mul_10);//PLL3��Ƶ10�� 5*10=50M

	RCC_PLL3Cmd(ENABLE);//ʹ��PLL3ʱ��

	while (RCC_GetFlagStatus(RCC_FLAG_PLL3RDY) == RESET)//�ȴ�PLL3ʹ�ܳɹ�
	{
	}

	RCC_MCOConfig(RCC_MCO_PLL3CLK);//ѡ��MCO��ʱ��ԴΪPLL3
#endif


}

/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void NVIC_Configuration(void)
;˵    ���� ETH  NVIC ����
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.12.15
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;            //���ļ��ڣ�NVIC�ṹ��

//	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);            //�⺯����������������λ�ú�ƫ�ƣ���������������FLASH������ƫ�ơ�
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);          //�⺯�����������ȼ����飺��ռ���ȼ��ʹ����ȼ�
													         //NVIC_PriorityGroup_2����ռ���ȼ�2λ �����ȼ�2λ
	NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;           //�����ж�ͨ��=��̫���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//������ռ���ȼ�=2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //���ô����ȼ�=0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);                          //�⺯��������NVIC_InitStructure�ṹ���ڵĲ�����ʼ��NVIC�Ĵ���
}


void ETHCFHAL_Iint(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ETH_MAC | RCC_AHBPeriph_ETH_MAC_Tx |
		RCC_AHBPeriph_ETH_MAC_Rx, ENABLE);	                                            //�⺯����ʹ��MAC��MAC���ͺ�MAC����ʱ��
	
	ETHCFHAL_GPIO_Config();
	NVIC_Configuration();
	Ethernet_Configuration();
	//ETH_Reinit();
	//ETH_WritePHYRegister(PHY_ADDRESS, 0x12, 0x30);
}



void ETH_Reinit()
{

	ETH_InitTypeDef ETH_InitStructure;  //���ļ�����ʼ����̫���õ��Ľṹ��

	ETH_DeInit();       //��λ��̫������Ĵ�����Ĭ��ֵ����ʹ�ܣ��ڽ�ֹ���ѻָ�Ĭ��ֵ

	ETH_SoftwareReset();//������λ��ͨ������ETH->DMABMR�Ĵ�����λ0ʵ��

	while (ETH_GetSoftwareResetStatus() == SET);//�ȴ�����λ�ɹ�

	ETH_StructInit(&ETH_InitStructure);//��ʼ���ṹ��ETH_InitStructure������ԱΪĬ��ֵ
									   //ETH_InitStructure�ṹ���ڳ�Ա�϶࣬�����Ĭ��ֵ���޸�һЩ�ؼ���Ա������Ӧ��ǰ����Ҫ
	ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;   			//������������Ӧ����
	ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;					//�رշ���
	ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable; 		//�ر��ش�����
	ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable; 	//�ر��Զ�ȥ��PDA/CRC���� 
	ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;						//�رս������е�֡
	ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;//�����������й㲥֡
	ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;			//�رջ��ģʽ�ĵ�ַ����  
	ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;//�����鲥��ַʹ��������ַ����   
	ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;	//�Ե�����ַʹ��������ַ���� 

#if  !CHECKSUM_GEN_ICMP    //�ж��Ƿ���Ӳ��У��,�ر�����У��
	ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable; 			//����ipv4��TCP/UDP/ICMP��֡У���ж��   
#endif
																					//������ʹ��֡У���ж�ع��ܵ�ʱ��һ��Ҫʹ�ܴ洢ת��ģʽ,�洢ת��ģʽ��Ҫ��֤����֡�洢��FIFO��,
																					//����MAC�ܲ���/ʶ���֡У��ֵ,����У����ȷ��ʱ��DMA�Ϳ��Դ���֡,����Ͷ�������֡
	ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable; //��������TCP/IP����֡
	ETH_InitStructure.ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;     //�����������ݵĴ洢ת��ģʽ    
	ETH_InitStructure.ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;   //�����������ݵĴ洢ת��ģʽ  

	ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;     	//��ֹת������֡  
	ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable;	//��ת����С�ĺ�֡ 
	ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Enable;  		//�򿪴����ڶ�֡����
	ETH_InitStructure.ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;  	//����DMA����ĵ�ַ���빦��
	ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Enable;            			//�����̶�ͻ������    
	ETH_InitStructure.ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;     		//DMA���͵����ͻ������Ϊ32������   
	ETH_InitStructure.ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;		    //DMA���յ����ͻ������Ϊ32������
	ETH_InitStructure.ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_2_1;
	EthInitStatus = ETH_Init(&ETH_InitStructure, PHY_ADDRESS);		                                //����ETH
	ETH_DMAITConfig(ETH_DMA_IT_NIS | ETH_DMA_IT_R, ENABLE);  	                    //ʹ����̫�������ж�	
}

/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void ETH_IRQHandler(void)
;˵    ���� ��̫���жϴ�������
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.12.15
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void ETH_IRQHandler(void)
{
	//����Ƿ��յ����ݰ�
	while (ETH_GetRxPktSize() != 0)
	{
		LwIP_Pkt_Handle();//�������ݺ���
	}

	/* Clear the Eth DMA Rx IT pending bits */
	ETH_DMAClearITPendingBit(ETH_DMA_IT_R);     //���DMA�жϱ�־λ
	ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);   //���DMA�����жϱ�־λ
}


void ETH_LinkScan(void)
{
	unsigned int  PHYIntStat = 0;
	unsigned int  status = 0;

	PHYIntStat = ETH_ReadPHYRegister(PHY_ADDRESS, PHY_MISR); //��ȡ�ж�״̬�Ĵ���
	if(PHYIntStat & PHYINT_SEEPLINK_STATUS)
	{
		status = ETH_ReadPHYRegister(PHY_ADDRESS, PHY_BSR);
	 //status = ETH_ReadPHYRegister(PHY_ADDRESS, PHY_BSR);
	 if (status &  (PHY_AutoNego_Complete | PHY_Linked_Status)) //��������
	 {
		 if (EthInitStatus == 0) //֮ǰδ��ʼ��
		 {
			 ETH_Reinit();
			 if (EthInitStatus)
			 {
				 lwipInitHQS();
				 httpd_init();

			 }

		 }
		 else
		 {
			/*set link up for re link callbalk function*/
			netif_set_link_up(&netif);
		 }
	 }
	 else   //����
	 {
		 netif_set_link_down(&netif);
	 }
	
	}
}




