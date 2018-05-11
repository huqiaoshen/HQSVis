/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include "lwip/opt.h"

#if 0 /* don't build, this is only a skeleton, see previous comment */

#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include "netif/etharp.h"
#include "netif/ppp_oe.h"

#include "stm32_eth.h"
/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif {
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
};

/* Forward declarations. */
static void  ethernetif_input(struct netif *netif);

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void
low_level_init(struct netif *netif)
{
  struct ethernetif *ethernetif = netif->state;
  
  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  netif->hwaddr[0] = ;
  ...
  netif->hwaddr[5] = ;

  /* maximum transfer unit */
  netif->mtu = 1500;
  
  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
 
  /* Do whatever else is needed to initialize interface. */  
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  struct ethernetif *ethernetif = netif->state;
  struct pbuf *q;

  initiate transfer();
  
#if ETH_PAD_SIZE
  pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

  for(q = p; q != NULL; q = q->next) {
    /* Send the data from the pbuf to the interface, one pbuf at a
       time. The size of the data in each pbuf is kept in the ->len
       variable. */
    send data from(q->payload, q->len);
  }

  signal that packet should be sent();

#if ETH_PAD_SIZE
  pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif
  
  LINK_STATS_INC(link.xmit);

  return ERR_OK;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *
low_level_input(struct netif *netif)
{
  struct ethernetif *ethernetif = netif->state;
  struct pbuf *p, *q;
  u16_t len;

  /* Obtain the size of the packet and put it into the "len"
     variable. */
  len = ;

#if ETH_PAD_SIZE
  len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

  /* We allocate a pbuf chain of pbufs from the pool. */
  p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
  
  if (p != NULL) {

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    /* We iterate over the pbuf chain until we have read the entire
     * packet into the pbuf. */
    for(q = p; q != NULL; q = q->next) {
      /* Read enough bytes to fill this pbuf in the chain. The
       * available data in the pbuf is given by the q->len
       * variable.
       * This does not necessarily have to be a memcpy, you can also preallocate
       * pbufs for a DMA-enabled MAC and after receiving truncate it to the
       * actually received size. In this case, ensure the tot_len member of the
       * pbuf is the sum of the chained pbuf len members.
       */
      read data into(q->payload, q->len);
    }
    acknowledge that packet has been read();

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.recv);
  } else {
    drop packet();
    LINK_STATS_INC(link.memerr);
    LINK_STATS_INC(link.drop);
  }

  return p;  
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
static void
ethernetif_input(struct netif *netif)
{
  struct ethernetif *ethernetif;
  struct eth_hdr *ethhdr;
  struct pbuf *p;

  ethernetif = netif->state;

  /* move received packet into a new pbuf */
  p = low_level_input(netif);
  /* no packet could be read, silently ignore this */
  if (p == NULL) return;
  /* points to packet payload, which starts with an Ethernet header */
  ethhdr = p->payload;

  switch (htons(ethhdr->type)) {
  /* IP or ARP packet? */
  case ETHTYPE_IP:
  case ETHTYPE_ARP:
#if PPPOE_SUPPORT
  /* PPPoE packet? */
  case ETHTYPE_PPPOEDISC:
  case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
    /* full packet send to tcpip_thread to process */
    if (netif->input(p, netif)!=ERR_OK)
     { LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
       pbuf_free(p);
       p = NULL;
     }
    break;

  default:
    pbuf_free(p);
    p = NULL;
    break;
  }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{
  struct ethernetif *ethernetif;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
    
  ethernetif = mem_malloc(sizeof(struct ethernetif));
  if (ethernetif == NULL) {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
    return ERR_MEM;
  }

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

  netif->state = ethernetif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;
  
  ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);
  
  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}

#endif /* 0 */


#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include "netif/etharp.h"
#include "netif/ppp_oe.h"

#include <string.h>
#include "stm32_eth.h"



//����������
#define IFNAME0 'Z'
#define IFNAME1 'R'

#define  ETH_DMARxDesc_FrameLengthShift           16         //DMA������������RDES0�����Ĵ���������֡���ȵ�λ��ƫ��ֵ
#define  ETH_ERROR                                ((u32)0)   //��������
#define  ETH_SUCCESS                              ((u32)1)   //�޴�����

#define ETH_RXBUFNB        5  //���ջ���������
#define ETH_TXBUFNB        5  //���ͻ���������

extern u8_t MACaddr[6];                           //MAC��ַ������Ψһ��
extern ETH_DMADESCTypeDef  *DMATxDescToSet;  //��ǰDMA����������ָ�룬����̫�����ļ��ж����
extern ETH_DMADESCTypeDef  *DMARxDescToGet;  //��ǰDMA����������ָ�룬����̫�����ļ��ж����

ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];                    //���ͺͽ���DMA����������
uint8_t Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE], Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];//���ͺͽ��ջ�����

																							 //����֡�ṹ�壬������ʹ�õ��������
typedef struct {
	u32_t length;                     //֡����
	u32_t buffer;                     //������
	ETH_DMADESCTypeDef *descriptor;   //ָ��DMA��������ָ��
}FrameTypeDef;


//ǰ�õĺ�������
FrameTypeDef ETH_RxPkt_ChainMode(void);       //������������
u32_t ETH_GetCurrentTxBuffer(void);           //��ȡ��ǰDMA���������������ݻ�����ָ��
u32_t ETH_TxPkt_ChainMode(u16 FrameLength);   //������������
//err_t ethernetif_input(struct netif *netif);  //�ϲ�ӿں���

											  //��ʼ������
static void low_level_init(struct netif *netif)
{
	uint8_t i;

	netif->hwaddr_len = ETHARP_HWADDR_LEN;  //����MAC��ַ����

	netif->hwaddr[0] = MACaddr[0];  //����MAC��ַ��6λ����ַΨһ�������ظ�
	netif->hwaddr[1] = MACaddr[1];
	netif->hwaddr[2] = MACaddr[2];
	netif->hwaddr[3] = MACaddr[3];
	netif->hwaddr[4] = MACaddr[4];
	netif->hwaddr[5] = MACaddr[5];

	netif->mtu = 1500;   //����䵥Ԫ

						 //������������
						 //NETIF_FLAG_BROADCAST�����㲥
						 //NETIF_FLAG_ETHARP����ARP����
						 //NETIF_FLAG_LINK_UP���ú�ӿڲ���һ����Ծ�����ӣ�Ҫ����Ӳ��У��
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

	//����������Ҫ��ʼ�����ͺͽ���DMA����������
	//107VCT6������ʽ�ṹ
	//����Ҫ�ȴ���DMA����������
	//DMA�������ڰ�����һ��ָ����պͷ��ͻ�������ָ�룬���ǻ�Ҫ�������պͷ��ͻ���������������
	ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);//��ʼ������DMA����������
	ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);//��ʼ������DMA����������

																	  //����DMA�����������ж�
	for (i = 0; i<ETH_RXBUFNB; i++)
	{
		ETH_DMARxDescReceiveITConfig(&DMARxDscrTab[i], ENABLE);
	}

#if  !CHECKSUM_GEN_ICMP    //�ж��Ƿ���Ӳ��У��,�ر�����У��
	//��������֡У�� 
	for (i = 0; i<ETH_TXBUFNB; i++)
	{
		ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
	}
#endif

	ETH_Start();//����MAC��DMA
}

//�������ݺ���
//��һ���򵥵Ŀ�ܺ�DMA�������Ľṹ
//����˼·����
//Ҫ���͵����ݴ������Ϊ������������pubf��
//DMA��������������ָ�򻺳�����ָ�룬��������Ҳ�����˻�����
//��������Ҫ�õ���������DMA������ָ�룬��������Ҫʵ��һ��ETH_GetCurrentTxBuffer����
//���������ǽ�pbuf�����ݿ�����������
//����ʹ�õ�������дһ�������������ݵĺ���ETH_TxPkt_ChainMode
//�⼸������ST�ٷ������˻���DP83848������
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
	struct pbuf *q; //��һ��pbuf���������ݴ濽���м�����
	int l = 0;      //����
	u8 *buffer = (u8 *)ETH_GetCurrentTxBuffer();//��ȡ��ǰDMA�ڻ�����ָ�룬��Ҫ���͵����ݣ�������������

	for (q = p; q != NULL; q = q->next)   //����forѭ������������
	{
		memcpy((u8_t*)&buffer[l], q->payload, q->len);
		l = l + q->len;
	}

	ETH_TxPkt_ChainMode(l);//��������

	return ERR_OK;
}

//�������ݺ���
//��һ���򵥵Ŀ�ܺ�DMA�������Ľṹ
//����˼·����
//���������յ����ݣ������ڽ��ջ�����������DMA����������ָ�����ָ��
//���ǻ�Ҫʵ��һ�������������ݵĺ���ETH_TxPkt_ChainMode��ͬ����һ��ST�ṩ������
//�õ������������ݺ�����Ҫ���俽����pbuf�ṹ�У���LWipʹ��
//��������������ݿ�����pbuf�󣬽�����Ϊ��������ֵ������
static struct pbuf * low_level_input(struct netif *netif)
{
	struct pbuf *p, *q; //pҪ���ص����ݣ�q��������ʱ�����ݴ�����
	u16_t len;          //������յ�����֡�ĳ���
	int l = 0;           //���ȣ�forʱ�ݴ��м�ֵ
	FrameTypeDef frame; //������
	u8 *buffer;         //���յ����ݵĵ�ַ

	p = NULL; //p��ָ��գ�����
	frame = ETH_RxPkt_ChainMode();//��������֡

	len = frame.length;//������֡���ȴ����len�ڴ���

	buffer = (u8 *)frame.buffer; //�õ���������ַ

	p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);//�ڴ�ط���ռ�

	if (p != NULL)//����ɹ�
	{
		for (q = p; q != NULL; q = q->next)//����forѭ����������
		{
			memcpy((u8_t*)q->payload, (u8_t*)&buffer[l], q->len);
			l = l + q->len;
		}
	}

	frame.descriptor->Status = ETH_DMARxDesc_OWN; //����DMAռ��������

	if ((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)  //ͨ���ж�ETH->DMASR�Ĵ���λ7���жϽ��ջ������ɲ�����
	{
		//���ջ����������ã�if����
		ETH->DMASR = ETH_DMASR_RBUS; //������ջ����������ñ�־
		ETH->DMARPDR = 0;//ͨ��дETH->DMARPDR�Ĵ������ָ�DMA����
	}

	return p;//��������
}

//LWip���õĽ������ݺ���
//��Ҫ���ǵ�����low_level_input����
err_t ethernetif_input(struct netif *netif)
{
	err_t err;
	struct pbuf *p;

	p = low_level_input(netif);//����low_level_input������������

	if (p == NULL) return ERR_MEM;//�����ݿɶ������ش������

	err = netif->input(p, netif);//����LWipԴ�봦������
	if (err != ERR_OK) //�������ʧ��
	{
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));//������Ϣ
		pbuf_free(p);//�ͷŵ�pbuf�ռ�
		p = NULL;
	}

	return err;
}


err_t ethernetif_init(struct netif *netif)
{
	LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
	netif->hostname = "lwip";//����
#endif 

							 //��ʼ��netif����ֶ�
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	netif->output = etharp_output;
	netif->linkoutput = low_level_output;

	low_level_init(netif);

	return ERR_OK;
}

//�����������ݺ���
FrameTypeDef ETH_RxPkt_ChainMode(void)
{
	u32 framelength = 0;             //��������
	FrameTypeDef frame = { 0,0 };      //֡�ṹ����

	if ((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) != (u32)RESET)//���DMAռ������������
	{
		frame.length = ETH_ERROR;   //��Ŵ������

		if ((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)  //������ͻ��治���ã�if����
		{
			ETH->DMASR = ETH_DMASR_RBUS; //������ջ����������ñ�־
			ETH->DMARPDR = 0;//ͨ��дETH->DMARPDR�Ĵ������ָ�DMA����
		}

		return frame; //����֡�ṹ
	}
	//����ϲ�if����������־��������CPUռ��
	//��Ҫ����3���ж�
	//ETH_DMARxDesc_ES�жϽ������Ƿ������������ʾû�д�����
	//ETH_DMARxDesc_LS�ж��Ƿ������һ��������
	//ETH_DMARxDesc_FS�ж��Ƿ������֡�ĵ�һ��������
	if (((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (u32)RESET) &&
		((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (u32)RESET) &&
		((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (u32)RESET))
	{
		//�������Ļ����õ�֡����ֵ��
		//DMA����������RDES0�����Ĵ���λ16-λ29���֡����ֵ
		//����16λ��Ȼ��Ҫ��ȥ4���Լ���CRCУ��
		framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> ETH_DMARxDesc_FrameLengthShift) - 4;

		frame.buffer = DMARxDescToGet->Buffer1Addr;	//�õ�������������Buffer1Addr��ַ����ָ�������ݻ�����
	}
	else//����ϲ�if������
	{
		framelength = ETH_ERROR;//��¼�������
	}

	frame.length = framelength; //��֡����ֵ����¼��frame�ṹ���е�length��Ա


	frame.descriptor = DMARxDescToGet;//frame�ṹ���е�descriptor��Աָ��ǰ��DMA����������

	DMARxDescToGet = (ETH_DMADESCTypeDef*)(DMARxDescToGet->Buffer2NextDescAddr);//����ǰ����DMA������ָ�룬ָ����һ������DMA�����е�DMA������  

	return (frame);  //����֡�ṹ
}

//�����������ݺ���
u32_t ETH_TxPkt_ChainMode(u16 FrameLength)
{
	if ((DMATxDescToSet->Status & ETH_DMATxDesc_OWN) != (u32)RESET)//���DMAռ������������
	{
		return ETH_ERROR;//���ش������
	}

	//���if����������ʾCPUռ��������
	DMATxDescToSet->ControlBufferSize = (FrameLength & ETH_DMATxDesc_TBS1);//���÷���֡����

	DMATxDescToSet->Status |= ETH_DMATxDesc_LS | ETH_DMATxDesc_FS;//ETH_DMATxDesc_LS��ETH_DMATxDesc_FS��1����ʾ֡�д���ˣ���һ�������һ���ֿ�

	DMATxDescToSet->Status |= ETH_DMATxDesc_OWN;//����������DMAʹ��

	if ((ETH->DMASR & ETH_DMASR_TBUS) != (u32)RESET)//������ͻ��治���ã�if����
	{
		ETH->DMASR = ETH_DMASR_TBUS;//������ͻ��治���ñ�־
		ETH->DMATPDR = 0;//дETH->DMATPDR�Ĵ���������ظ���������
	}

	DMATxDescToSet = (ETH_DMADESCTypeDef*)(DMATxDescToSet->Buffer2NextDescAddr);//����ǰ����DMA������ָ�룬ָ����һ������DMA�����е�DMA������     


	return ETH_SUCCESS;   //���سɹ�����
}

//��ȡ����DMA�������µĻ�����
u32_t ETH_GetCurrentTxBuffer(void)
{
	return (DMATxDescToSet->Buffer1Addr);   //�õ�DMA��������Buffer1Addr��ַ��
}






