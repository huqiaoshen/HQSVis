/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2017/12/21
* @brief   TCP Service 相关.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#include "lwip/tcp.h"
#include "HQSlwip.h"
#include "HQS_typedef.h"

typedef struct TcpServiceHQSPCBIP_t
{
	struct tcp_pcb *namePcb;
	uint16    local_port;
	ip_addr_t remote_ip;
	uint16    remote_port;
	uint8     state;
}TcpServiceHQSPCBIP_t;


// 创建PCB
void TcpServiceCreate(TcpServiceHQSPCBIP_t *namePcbIP);
//void TcpServiceCreate();

//监听                 
void TcpServiceListen(TcpServiceHQSPCBIP_t *namePcbIP);

//直接发送(所有链接)
err_t TCPServiceSend(TcpServiceHQSPCBIP_t *namePcbIP, unsigned char *buff, unsigned int length);

//接受回调函数
err_t TcpServerAcceptCB(void *arg, struct tcp_pcb *newpcb, err_t err);


//关闭连接 回调 赋空



//回调 回调
err_t TcpServerSendCB(void *arg, struct tcp_pcb *tpcb, u16_t len);

//接收 回调
err_t TcpServerRecvCB(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

//轮回 回调
err_t  TcpServerPollCB(void *arg, struct tcp_pcb *tpcb);

//错误处理 回调
void  TcpServerErrCB(void *arg, err_t err);



//直接发送
//err_t TCPServiceSend(TcpServiceHQSPCBIP_t *namePcbIP, unsigned char *buff, unsigned int length);








