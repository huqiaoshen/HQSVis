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
#include "lwip/tcp.h"
#include "HQS_typedef.h"

typedef struct TcpClientHQSPCBIP_t
{
	struct tcp_pcb *namePcb;
	uint16    local_port;
	ip_addr_t remote_ip;
	uint16    remote_port;
	uint8     state;
//	TcpClientHQSPCBIP_t * localP;
}TcpClientHQSPCBIP_t;


// 创建PCB
void TcpClientCreate(TcpClientHQSPCBIP_t *namePcbIP);


//链接服务器                  
void TcpClientConnService(TcpClientHQSPCBIP_t *namePcbIP);



//接受回调函数
err_t TcpClientCallBack(void *arg, struct tcp_pcb *tpcb, err_t err);



//关闭连接 回调 赋空



//回调 回调
err_t TcpClientSendCB(void *arg, struct tcp_pcb *tpcb,u16_t len);

//接收 回调
err_t TcpClientRecvCB(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

//轮回 回调
err_t TcpClientPollCB(void *arg, struct tcp_pcb *tpcb);

//错误处理 回调
void TcpClientErrCB(void *arg, err_t err);



//直接发送
err_t TCPClientSend(TcpClientHQSPCBIP_t *namePcbIP, unsigned char *buff, unsigned int length);