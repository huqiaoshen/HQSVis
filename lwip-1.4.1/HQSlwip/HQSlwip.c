
#include "HQSlwip.h"

//ethernetif.c �ļ��ں�������
err_t ethernetif_init(struct netif *netif); 
err_t ethernetif_input(struct netif *netif);

struct netif netif;             //����һ��ȫ�ֵ�����ӿڣ�ע����������Ҫ�õ�  

u8_t MACaddr[6] = { 6,0,6,0,6,1 };  //MAC��ַ������Ψһ��

#if LWIP_DHCP                   //�������DHCP
u32 DHCPfineTimer = 0;	        //DHCP��ϸ������ʱ��
u32 DHCPcoarseTimer = 0;	    //DHCP�ֲڴ�����ʱ��
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
	struct ip_addr ipaddr;     //����IP��ַ�ṹ��
	struct ip_addr netmask;    //������������ṹ��
	struct ip_addr gw;         //�������ؽṹ��
	mem_init();  //��ʼ����̬�ڴ��
	memp_init(); //��ʼ���ڴ��
	lwip_init(); //��ʼ��LWIP�ں�

#if LWIP_DHCP     //�������DHCP���Զ���ȡIP
	ipaddr.addr = 0;
	netmask.addr = 0;
	gw.addr = 0;
#else            //������DHCP��ʹ�þ�̬IP
	IP4_ADDR(&ipaddr, 192, 168, 1, 205);      //����IP��ַ
	IP4_ADDR(&netmask, 255, 255, 255, 0);   //������������
	IP4_ADDR(&gw, 192, 168, 1, 1);          //��������
#endif

	ETH_MACAddressConfig(ETH_MAC_Address0, MACaddr);  //����MAC��ַ
	//ע����������   ethernetif_init��������Ҫ�Լ�ʵ�֣���������netif����ֶΣ��Լ���ʼ���ײ�Ӳ����
	netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

	//��ע����������ע�����������ΪĬ������
	netif_set_default(&netif);


#if LWIP_DHCP           //���������DHCP��λ
	dhcp_start(&netif);   //����DHCP
#endif

	 //������
	netif_set_up(&netif);  

	netif_set_link_callback(&netif, eth_re_link);

}







//�������ݺ���
void LwIP_Pkt_Handle(void)
{
	//�����绺�����ж�ȡ���յ������ݰ������䷢�͸�LWIP���� 
	ethernetif_input(&netif);
}




__IO uint32_t TCPTimer = 0;     //TCP��ѯ��ʱ�� 
__IO uint32_t ARPTimer = 0;     //ARP��ѯ��ʱ��
__IO uint32_t CLIENTTimer = 0;  //�ͻ��˷��ͼ�ʱ��
//LWIP����������
void lwip_periodic_handle(void)
{

	//ÿ200ms�ͻ��˷���һ������
	if (LWipTimeClk - CLIENTTimer >= 200)
	{
		CLIENTTimer = LWipTimeClk;	
	}
#if LWIP_TCP
	//ÿ250ms����һ��tcp_tmr()����
	if (LWipTimeClk - TCPTimer >= 50)
	{
		TCPTimer = LWipTimeClk;
		tcp_tmr();
	}
#endif
	//ARPÿ5s�����Ե���һ��
	if ((LWipTimeClk - ARPTimer) >= ARP_TMR_INTERVAL)
	{
		ARPTimer = LWipTimeClk;
		etharp_tmr();
	}
#if LWIP_DHCP //���ʹ��DHCP�Ļ�
	//ÿ500ms����һ��dhcp_fine_tmr()
	if (LWipTime - DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
	{
		DHCPfineTimer = LWipTime;
		dhcp_fine_tmr();
	}

	//ÿ60sִ��һ��DHCP�ֲڴ���
	if (LWipTime - DHCPcoarseTimer >= DHCP_COARSE_TIMER_MSECS)
	{
		DHCPcoarseTimer = LWipTime;
		dhcp_coarse_tmr();
	}
#endif
}



/******************************************************************************************************
ʵ��ʹ���У���Ҫ����IP��һ����������������������һ���µķ�ʽ��������¼
netif_set_addr(); ��������������IP�����أ��������룬�ڲ�ͨ������netif_set_ipaddr(), netif_set_gw(), netif_set_netmask()��
netif_set_up()��Ϊʹ������
netif_set_down()���������ã�����������IPʱҪ�Ƚ��������������ã�Ȼ������
******************************************************************************************************/

void lwipSetLocalIpHQS(struct ip_addr ipaddr,struct ip_addr netmask,struct ip_addr gw)
{
	netif_set_down(&netif);
	netif_set_addr(&netif, &ipaddr, &netmask, &gw);
	netif_set_up(&netif);

	//STM32���� �������
}

void lwipSetLocalMACHQS()
{
	ETH_MACAddressConfig(ETH_MAC_Address0, MACaddr);  //����MAC��ַ
	netif_set_down(&netif);
	//netif_set_addr(&netif, &ipaddr, &netmask, &gw);
	netif_set_up(&netif);

	//STM32���� �������
}
