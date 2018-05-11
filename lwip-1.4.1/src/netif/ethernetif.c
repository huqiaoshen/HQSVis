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



//网卡的名字
#define IFNAME0 'Z'
#define IFNAME1 'R'

#define  ETH_DMARxDesc_FrameLengthShift           16         //DMA接收描述符，RDES0软件寄存器中描述帧长度的位的偏移值
#define  ETH_ERROR                                ((u32)0)   //出错代码
#define  ETH_SUCCESS                              ((u32)1)   //无错代码

#define ETH_RXBUFNB        5  //接收缓冲器数量
#define ETH_TXBUFNB        5  //发送缓冲器数量

extern u8_t MACaddr[6];                           //MAC地址，具有唯一性
extern ETH_DMADESCTypeDef  *DMATxDescToSet;  //当前DMA发送描述符指针，在以太网库文件中定义的
extern ETH_DMADESCTypeDef  *DMARxDescToGet;  //当前DMA接收描述符指针，在以太网库文件中定义的

ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];                    //发送和接收DMA描述符数组
uint8_t Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE], Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];//发送和接收缓冲区

																							 //数据帧结构体，和我们使用的网卡相关
typedef struct {
	u32_t length;                     //帧长度
	u32_t buffer;                     //缓冲区
	ETH_DMADESCTypeDef *descriptor;   //指向DMA描述符的指针
}FrameTypeDef;


//前置的函数声明
FrameTypeDef ETH_RxPkt_ChainMode(void);       //网卡接收数据
u32_t ETH_GetCurrentTxBuffer(void);           //获取当前DMA发送描述符下数据缓冲区指针
u32_t ETH_TxPkt_ChainMode(u16 FrameLength);   //网卡发送数据
//err_t ethernetif_input(struct netif *netif);  //上层接口函数

											  //初始化函数
static void low_level_init(struct netif *netif)
{
	uint8_t i;

	netif->hwaddr_len = ETHARP_HWADDR_LEN;  //设置MAC地址长度

	netif->hwaddr[0] = MACaddr[0];  //设置MAC地址，6位，地址唯一，不能重复
	netif->hwaddr[1] = MACaddr[1];
	netif->hwaddr[2] = MACaddr[2];
	netif->hwaddr[3] = MACaddr[3];
	netif->hwaddr[4] = MACaddr[4];
	netif->hwaddr[5] = MACaddr[5];

	netif->mtu = 1500;   //最大传输单元

						 //设置网卡功能
						 //NETIF_FLAG_BROADCAST允许广播
						 //NETIF_FLAG_ETHARP开启ARP功能
						 //NETIF_FLAG_LINK_UP设置后接口产生一个活跃的链接，要开启硬件校验
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

	//接下来我们要初始化发送和接收DMA描述符链表
	//107VCT6采用链式结构
	//我们要先创建DMA描述符数组
	//DMA描述符内包含了一个指向接收和发送缓冲区的指针，我们还要创建接收和发送缓冲区，两个数组
	ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);//初始化发送DMA描述符链表
	ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);//初始化接收DMA描述符链表

																	  //开启DMA描述符接收中断
	for (i = 0; i<ETH_RXBUFNB; i++)
	{
		ETH_DMARxDescReceiveITConfig(&DMARxDscrTab[i], ENABLE);
	}

#if  !CHECKSUM_GEN_ICMP    //判断是否开启硬件校验,关闭软件校验
	//开启发送帧校验 
	for (i = 0; i<ETH_TXBUFNB; i++)
	{
		ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
	}
#endif

	ETH_Start();//开启MAC和DMA
}

//发送数据函数
//看一看简单的框架和DMA描述符的结构
//整理思路如下
//要发送的数据存放在最为参数传进来的pubf下
//DMA发送描述符内有指向缓冲器的指针，而且我们也设置了缓冲区
//我们首先要得到描述符的DMA缓冲区指针，所以我们要实现一个ETH_GetCurrentTxBuffer函数
//接下来我们将pbuf的数据拷贝到缓冲区
//根据使用的网卡，写一个网卡发送数据的函数ETH_TxPkt_ChainMode
//这几个函数ST官方都给了基于DP83848的例程
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
	struct pbuf *q; //顶一个pbuf缓冲区，暂存拷贝中间数据
	int l = 0;      //长度
	u8 *buffer = (u8 *)ETH_GetCurrentTxBuffer();//获取当前DMA内缓冲区指针，将要发送的数据，拷贝到缓冲区

	for (q = p; q != NULL; q = q->next)   //利用for循环，拷贝数据
	{
		memcpy((u8_t*)&buffer[l], q->payload, q->len);
		l = l + q->len;
	}

	ETH_TxPkt_ChainMode(l);//发送数据

	return ERR_OK;
}

//接收数据函数
//看一看简单的框架和DMA描述符的结构
//整理思路如下
//当网卡接收到数据，会存放在接收缓冲区，接收DMA描述符下有指向其的指针
//我们还要实现一个网卡接收数据的函数ETH_TxPkt_ChainMode，同发送一样ST提供了例程
//得到缓冲区的数据后，我们要将其拷贝到pbuf结构中，供LWip使用
//所以我们最后将数据拷贝到pbuf后，将它作为函数返回值，返回
static struct pbuf * low_level_input(struct netif *netif)
{
	struct pbuf *p, *q; //p要返回的数据，q拷贝数据时用于暂存数据
	u16_t len;          //保存接收到数据帧的长度
	int l = 0;           //长度，for时暂存中间值
	FrameTypeDef frame; //接受侦
	u8 *buffer;         //接收到数据的地址

	p = NULL; //p向指向空，待用
	frame = ETH_RxPkt_ChainMode();//接收数据帧

	len = frame.length;//将数据帧长度存放在len内待用

	buffer = (u8 *)frame.buffer; //得到数据区地址

	p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);//内存池分配空间

	if (p != NULL)//分配成功
	{
		for (q = p; q != NULL; q = q->next)//利用for循环拷贝数据
		{
			memcpy((u8_t*)q->payload, (u8_t*)&buffer[l], q->len);
			l = l + q->len;
		}
	}

	frame.descriptor->Status = ETH_DMARxDesc_OWN; //设置DMA占用描述符

	if ((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)  //通过判断ETH->DMASR寄存器位7，判断接收缓冲区可不可用
	{
		//接收缓冲区不可用，if成立
		ETH->DMASR = ETH_DMASR_RBUS; //清除接收缓冲区不可用标志
		ETH->DMARPDR = 0;//通过写ETH->DMARPDR寄存器，恢复DMA接收
	}

	return p;//返回数据
}

//LWip调用的接收数据函数
//主要就是调用了low_level_input函数
err_t ethernetif_input(struct netif *netif)
{
	err_t err;
	struct pbuf *p;

	p = low_level_input(netif);//调用low_level_input函数接收数据

	if (p == NULL) return ERR_MEM;//无数据可读，返回错误代码

	err = netif->input(p, netif);//调用LWip源码处理数据
	if (err != ERR_OK) //如果处理失败
	{
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));//调试信息
		pbuf_free(p);//释放掉pbuf空间
		p = NULL;
	}

	return err;
}


err_t ethernetif_init(struct netif *netif)
{
	LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
	netif->hostname = "lwip";//命名
#endif 

							 //初始化netif相关字段
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	netif->output = etharp_output;
	netif->linkoutput = low_level_output;

	low_level_init(netif);

	return ERR_OK;
}

//网卡接收数据函数
FrameTypeDef ETH_RxPkt_ChainMode(void)
{
	u32 framelength = 0;             //变量待用
	FrameTypeDef frame = { 0,0 };      //帧结构待用

	if ((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) != (u32)RESET)//如果DMA占用描述符成立
	{
		frame.length = ETH_ERROR;   //存放错误代码

		if ((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)  //如果发送缓存不可用，if成立
		{
			ETH->DMASR = ETH_DMASR_RBUS; //清除接收缓冲区不可用标志
			ETH->DMARPDR = 0;//通过写ETH->DMARPDR寄存器，恢复DMA接收
		}

		return frame; //返回帧结构
	}
	//如果上步if不成立，标志描述符由CPU占用
	//又要进行3个判断
	//ETH_DMARxDesc_ES判断接收中是否出错，成立表示没有错误发生
	//ETH_DMARxDesc_LS判断是否到了最后一个缓冲区
	//ETH_DMARxDesc_FS判断是否包含了帧的第一个缓冲区
	if (((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (u32)RESET) &&
		((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (u32)RESET) &&
		((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (u32)RESET))
	{
		//都成立的话，得到帧长度值，
		//DMA接收描述符RDES0软件寄存器位16-位29存放帧长度值
		//右移16位，然后还要减去4个自己的CRC校验
		framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> ETH_DMARxDesc_FrameLengthShift) - 4;

		frame.buffer = DMARxDescToGet->Buffer1Addr;	//得到接收描述符下Buffer1Addr地址，它指向了数据缓冲区
	}
	else//如果上步if不成立
	{
		framelength = ETH_ERROR;//记录错误代码
	}

	frame.length = framelength; //将帧长度值，记录在frame结构体中的length成员


	frame.descriptor = DMARxDescToGet;//frame结构体中的descriptor成员指向当前的DMA接收描述符

	DMARxDescToGet = (ETH_DMADESCTypeDef*)(DMARxDescToGet->Buffer2NextDescAddr);//将当前接收DMA描述符指针，指向下一个接收DMA链表中的DMA描述符  

	return (frame);  //返回帧结构
}

//网卡发送数据函数
u32_t ETH_TxPkt_ChainMode(u16 FrameLength)
{
	if ((DMATxDescToSet->Status & ETH_DMATxDesc_OWN) != (u32)RESET)//如果DMA占用描述符成立
	{
		return ETH_ERROR;//返回错误代码
	}

	//如果if不成立，表示CPU占用描述符
	DMATxDescToSet->ControlBufferSize = (FrameLength & ETH_DMATxDesc_TBS1);//设置发送帧长度

	DMATxDescToSet->Status |= ETH_DMATxDesc_LS | ETH_DMATxDesc_FS;//ETH_DMATxDesc_LS和ETH_DMATxDesc_FS置1，表示帧中存放了，第一个和最后一个分块

	DMATxDescToSet->Status |= ETH_DMATxDesc_OWN;//把描述符给DMA使用

	if ((ETH->DMASR & ETH_DMASR_TBUS) != (u32)RESET)//如果发送缓存不可用，if成立
	{
		ETH->DMASR = ETH_DMASR_TBUS;//清除发送缓存不可用标志
		ETH->DMATPDR = 0;//写ETH->DMATPDR寄存器，以求回复发送流程
	}

	DMATxDescToSet = (ETH_DMADESCTypeDef*)(DMATxDescToSet->Buffer2NextDescAddr);//将当前发送DMA描述符指针，指向下一个发送DMA链表中的DMA描述符     


	return ETH_SUCCESS;   //返回成功代码
}

//获取发送DMA描述符下的缓冲区
u32_t ETH_GetCurrentTxBuffer(void)
{
	return (DMATxDescToSet->Buffer1Addr);   //得到DMA描述符内Buffer1Addr地址。
}







