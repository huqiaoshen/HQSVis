
#include "includeshqs.h"
#include "HQSUDP.h"
#include "HQSTcpClient.h"
#include "HQSTcpService.h"
#include "httpd.h"

void lwip_UP(void)
{
	ETH_LinkScan();
	LWipTimeClk++;
	lwip_periodic_handle();
	//Udp_QuerySend_Data();
}

TcpServiceHQSPCBIP_t tcpServiceTest;
TcpClientHQSPCBIP_t  tcpClientTest;
struct ip_addr serviceIp;
int main()
{
	//硬件初始化
	HQSHALIoOutIint();
	USART1_Init(9600);
	USART2_Init(9600);
	ETHCFHAL_Iint();
	PVDInint();

	//系统初始化
	HQSmemPithyInit();
	OsHQSInit();
	Delay_Init();

//	TIMcount_Init();

	uint16  bkpdata = BKPHALRead(BKP_DR1);
	if(bkpdata != 0x1234)
	{
		BKPHALWirte(BKP_DR1,0x1234);
		USART1_Send_String("BKP_DR1 wirt");
		RTCHALIint();
	}
	else
	{
		NVIC_InitTypeDef NVIC_InitStruct;
		//RCT 中断分组设置
		NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);//中断配置
		RTC_ITConfig(RTC_IT_SEC, ENABLE); //使能 RTC 秒中断
	}
	//软件初始化
	HQSIoOutIint();
	USART1_Send_String("hello");
	//lwipInitHQS();
	//UdpRemoteipInit();

	//tcpServiceTest.local_port = 5000;
	//TcpServiceCreate(&tcpServiceTest);
	//TcpServiceListen(&tcpServiceTest);
	//

	//tcpClientTest.local_port = 54321;
	//IP4_ADDR(&(tcpClientTest.remote_ip), 192, 168, 1, 242);      //设置IP地址
	//tcpClientTest.remote_port = 8000;
	//TcpClientCreate(&tcpClientTest);
	//TcpClientConnService(&tcpClientTest);
	//
	//httpd_init();

	HQSIoOutSetBlink(RUN_LED_G, IOOUTHQS_MODE_BLINK, 2, 50, 0);
	OsHQSTaskCreate(0, HQSIoOutUpDate , 10);
	OsHQSTaskCreate(1,         lwip_UP,  5);
	OsHQSRun();
}





