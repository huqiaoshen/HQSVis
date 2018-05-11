
#include "HQSlwip.h"

//ethernetif.c 文件内函数声明
err_t ethernetif_init(struct netif *netif); 
err_t ethernetif_input(struct netif *netif);

struct netif netif;             //定义一个全局的网络接口，注册网卡函数要用到  

u8_t MACaddr[6] = { 6,0,6,0,6,1 };  //MAC地址，具有唯一性

#if LWIP_DHCP                   //如果开启DHCP
u32 DHCPfineTimer = 0;	        //DHCP精细处理计时器
u32 DHCPcoarseTimer = 0;	    //DHCP粗糙处理计时器
#endif

void eth_re_link(struct netif *netif)
{
	if (netif_is_link_up(netif)) 
	{/*link up process*/

	}
	else
	{/*link down process*/

	}
}

void lwipInitHQS(void)
{
	struct ip_addr ipaddr;     //定义IP地址结构体
	struct ip_addr netmask;    //定义子网掩码结构体
	struct ip_addr gw;         //定义网关结构体
	mem_init();  //初始化动态内存堆
	memp_init(); //初始化内存池
	lwip_init(); //初始化LWIP内核

#if LWIP_DHCP     //如果开启DHCP，自动获取IP
	ipaddr.addr = 0;
	netmask.addr = 0;
	gw.addr = 0;
#else            //不开启DHCP，使用静态IP
	IP4_ADDR(&ipaddr, 192, 168, 1, 205);      //设置IP地址
	IP4_ADDR(&netmask, 255, 255, 255, 0);   //设置子网掩码
	IP4_ADDR(&gw, 192, 168, 1, 1);          //设置网关
#endif

	ETH_MACAddressConfig(ETH_MAC_Address0, MACaddr);  //配置MAC地址
	//注册网卡函数   ethernetif_init函数，需要自己实现，用于配置netif相关字段，以及初始化底层硬件。
	netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

	//将注册网卡函数注册的网卡设置为默认网卡
	netif_set_default(&netif);


#if LWIP_DHCP           //如果开启了DHCP复位
	dhcp_start(&netif);   //开启DHCP
#endif

	 //打开网卡
	netif_set_up(&netif);  

	netif_set_link_callback(&netif, eth_re_link);

}







//接收数据函数
void LwIP_Pkt_Handle(void)
{
	//从网络缓冲区中读取接收到的数据包并将其发送给LWIP处理 
	ethernetif_input(&netif);
}




__IO uint32_t TCPTimer = 0;     //TCP查询计时器 
__IO uint32_t ARPTimer = 0;     //ARP查询计时器
__IO uint32_t CLIENTTimer = 0;  //客户端发送计时器
//LWIP周期性任务
void lwip_periodic_handle(void)
{

	//每200ms客户端发送一次数据
	if (LWipTimeClk - CLIENTTimer >= 200)
	{
		CLIENTTimer = LWipTimeClk;	
	}
#if LWIP_TCP
	//每250ms调用一次tcp_tmr()函数
	if (LWipTimeClk - TCPTimer >= 50)
	{
		TCPTimer = LWipTimeClk;
		tcp_tmr();
	}
#endif
	//ARP每5s周期性调用一次
	if ((LWipTimeClk - ARPTimer) >= ARP_TMR_INTERVAL)
	{
		ARPTimer = LWipTimeClk;
		etharp_tmr();
	}
#if LWIP_DHCP //如果使用DHCP的话
	//每500ms调用一次dhcp_fine_tmr()
	if (LWipTime - DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
	{
		DHCPfineTimer = LWipTime;
		dhcp_fine_tmr();
	}

	//每60s执行一次DHCP粗糙处理
	if (LWipTime - DHCPcoarseTimer >= DHCP_COARSE_TIMER_MSECS)
	{
		DHCPcoarseTimer = LWipTime;
		dhcp_coarse_tmr();
	}
#endif
}



/******************************************************************************************************
实际使用中，需要更改IP，一般是做重启操作，但看到一个新的方式，做个记录
netif_set_addr(); 用于重设网卡的IP，网关，子网掩码，内部通过调用netif_set_ipaddr(), netif_set_gw(), netif_set_netmask()，
netif_set_up()，为使能网卡
netif_set_down()，网卡禁用，在重新设置IP时要先禁用网卡，在设置，然后开启。
******************************************************************************************************/

void lwipSetLocalIpHQS(struct ip_addr ipaddr,struct ip_addr netmask,struct ip_addr gw)
{
	netif_set_down(&netif);
	netif_set_addr(&netif, &ipaddr, &netmask, &gw);
	netif_set_up(&netif);

	//STM32保存 相关设置
}

void lwipSetLocalMACHQS()
{
	ETH_MACAddressConfig(ETH_MAC_Address0, MACaddr);  //配置MAC地址
	netif_set_down(&netif);
	//netif_set_addr(&netif, &ipaddr, &netmask, &gw);
	netif_set_up(&netif);

	//STM32保存 相关设置
}

