/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2017/12/16
* @brief   LWIP ��ʼ�����������.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/


#include "stm32f10x.h"
#include "sys_arch.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/init.h"
#include "lwip/timers.h"
#include "lwip/tcp_impl.h"
#include "lwip/ip_frag.h"
#include "lwip/tcpip.h"
#include "stm32_eth.h"
#include <stdio.h>
#include <string.h>

extern struct netif netif;             //����һ��ȫ�ֵ�����ӿڣ�ע����������Ҫ�õ�  

void lwipInitHQS(void);
void lwip_periodic_handle(void);



