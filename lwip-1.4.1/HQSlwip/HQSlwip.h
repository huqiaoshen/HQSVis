/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2017/12/16
* @brief   LWIP 初始化及相关设置.
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

extern struct netif netif;             //定义一个全局的网络接口，注册网卡函数要用到  

void lwipInitHQS(void);
void lwip_periodic_handle(void);




