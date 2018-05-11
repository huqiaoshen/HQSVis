/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2017/12/17
* @brief   UDP 相关.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#include "HQSlwip.h"
#include "lwip/udp.h"
#include "HQS_typedef.h"

void UdpRemoteipInit(void);

void UdpSetRemoteip(void);

//询问模式 接收(回调函数)
void Udp_QueryRecv(void *arg, struct udp_pcb *pcb, struct pbuf *p,
	ip_addr_t *addr, u16_t port);

//发送
void Udp_QuerySend_Data();


//发送
void Udp_Send_Data();


//关闭
void Udp_Conn_Close();




